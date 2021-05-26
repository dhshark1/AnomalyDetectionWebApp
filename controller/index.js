const express = require('express')
const flleupload = require('express-fileupload')
const model = require('../model/detector')
var jsdom = require("jsdom");
const { JSDOM } = jsdom;
const { window } = new JSDOM();
const { document } = (new JSDOM('')).window;
global.document = document;

const app = express();
app.use(express.urlencoded({ 
  extended: false
}))

app.use(flleupload())
app.use(express.static(('../view')))

app.get("/", (req,res) => {
    res.sendFile("./index.html");
}) 

const jsonToElement = (data) => {
  let col = ["row number", "correlated features"];
  let table = document.createElement('table');
  table.setAttribute("style", "border:5px solid black;border-collapse:collapse;width:100%;padding:8px;text-align:center;font-size:25px;")
  let tr = table.insertRow(-1);
  for (let i = 0; i < col.length; i++) {
    let th = document.createElement("th");
    th.innerHTML = col[i];
    th.setAttribute("style", "border:5px solid black;text-align:center;font-size:35px;font-family: 'Oxygen', sans-serif;")
    tr.appendChild(th);
  }
  for(const [key, value] of Object.entries(data)) {
    tr = table.insertRow(-1);
    tr.setAttribute("style", "border:5px solid black;border-collapse:collapse;width:100%;padding:8px;text-align:center;font-size:25px;background-color: #f2f2f2;")
    let tabCell1 = tr.insertCell(-1);
    tabCell1.setAttribute("style", "border:5px solid black;text-align:center;font-size:25px;font-family: 'Oxygen', sans-serif;")
    tabCell1.innerHTML = key;
    let tabCell2 = tr.insertCell(-1);
    tabCell2.setAttribute("style", "border:5px solid black;text-align:center;font-size:25px;font-family: 'Oxygen', sans-serif;")
    tabCell2.innerHTML = value;
  }
  return table.outerHTML;
  }

app.post("/detect",(req,res)=>  {
  var myAlgorithm = req.body.myAlgorithm //anomaly detector kind
  if(req.files){ //csv files - train , test
    var testFile = req.files.train_file
    var trainFile = req.files.test_file
    const promise1 = new Promise((resolve, reject) => {
      model.detect(myAlgorithm,trainFile.data.toString(), testFile.data.toString(), resolve) 
    });
    promise1.then((value) => {
      console.log(value);
      //generate view...
      res.write(jsonToElement(value));
      res.end();
    });
  }
  
})

app.listen(8080, ()=> console.log('listen to my friends'))
