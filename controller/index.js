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
}) ;

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
      //res.write(jsonToElement(value));
      res.write(JSON.stringify(value))
      res.end();
    });
  }
  
})

app.listen(8080, ()=> console.log('listen to my friends'))
