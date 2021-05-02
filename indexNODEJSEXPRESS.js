const express = require('express')
const app = express()
const port = 9876
// var bodyParser = require('body-parser')
// app.use(bodyParser.json())

app.use(express.json());
app.use('/', express.static('./public'));

const models = [
    {id: 66, upload_time: 00000, status: "pending"},
    {id: 42, upload_time: 11111, status:"ready"}
]

app.get('/api/model/:id', (req, res) => {
  const model = models.find(c => c.id === parseInt(req.params.id));
  if (!model) res.status(404).send("the model with the given id is invalid");

  res.send(model);
})
app.get('/api/models/', (req, res) => {
  // res.send("danidin");
  res.send({name:"danidin"})
})
app.post('/api/model?:model_type', (req, res) => {
//TODO: need to send to c++ body according to model type
  var d = new Date();
  d = new Date(d.getTime());
  var date_format_str = d.getFullYear().toString()+"-"+((d.getMonth()+1).toString().length==2?(d.getMonth()+1).toString():"0"+(d.getMonth()+1).toString())+"-"+(d.getDate().toString().length==2?d.getDate().toString():"0"+d.getDate().toString())+"T"+(d.getHours().toString().length==2?d.getHours().toString():"0"+d.getHours().toString())+":"+((parseInt(d.getMinutes()/5)*5).toString().length==2?(parseInt(d.getMinutes()/5)*5).toString():"0"+(parseInt(d.getMinutes()/5)*5).toString())+":00"+((d.getTimezoneOffset()/60).toString().length==2?(d.getTimezoneOffset()/60).toString():"0"+(d.getTimezoneOffset()/60).toString())+".00";
  const model = {
    id: models.length+1,
    upload_time: date_format_str,
    status: "pending"
  };
  models.push(model);
  res.send(model);   
})
app.post('/api/anomaly?:model_id', (req, res) => {
    //body - predict data (test flight)
    //query params- int 
    const model = models.find(c => c.id === parseInt(req.params.id));
    if (!model) res.status(404).send("the model with the given id is invalid");

    //send to c++ model's data and body's data


})
app.delete('/api/model/:id', (req, res) => {
  //look up the model
  //if it doesnt exist, return 404
  const model = models.find(c => c.id === parseInt(req.params.id));
  if (!model) res.status(404).send("the model ID given was not found")

  //otherwise delete
  const index = models.indexOf(model);
  models.splice(index, 1);

  //return the same model
  res.send(model);
})
app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
