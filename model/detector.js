var net = require('net')

function detect(myAlgorithm, TrainCSV, TestCSV, resolve) {
    console.log("detect has been called")
    
    var client = new net.Socket();
    client.connect(34321, '127.0.0.1', function() {
        console.log('Connected');
        client.write(myAlgorithm+'\n');
        i = 0;
    });
    var jsonAccumaltor = {};
    

    client.on('data', (data)=> {
      
      
        s = data.toString().slice(0,4);
        console.log("data is: "+data.toString());
        
        switch (s) {
            case "Welc":
              if (i==0)
                client.write('1\n');
              if (i==1)
                client.write('3\n');
              if (i==2)
                client.write('4\n');
              if (i==3)
                client.write('6\n');
              i++;
              break;
            case "Anom":
                stop = false
                data.toString().split("\n").slice(1, -1).forEach((row)=> {
                  if(row === "Done.")
                  {console.log("ROE" + row)
                  stop = true;}
                  if(!stop)
                   { jsonAccumaltor[row.split('\t')[0]] = row.split('\t')[1];}
                });
                console.log("final json to be sent: " + jsonAccumaltor);
                resolve(jsonAccumaltor);
                break;
                //for
            case "E404":
                
                break;
            case "Plea":
              if (i-1==0){
                TrainCSV.split("\n").forEach((row)=> {
                    client.write(row+"\n")
                })
                client.write("done\n")
              }
              if (i-1==1){
                TestCSV.split("\n").forEach((row)=> {
                    client.write(row+"\n")
                })
                client.write("done\n")
              }
              break;
          }
          
    });

    client.on('end', () => { 
        console.log('CLIENT: I disconnected from the server.'); 
      }) 

}


module.exports.detect = detect
