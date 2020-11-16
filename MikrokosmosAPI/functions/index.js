/*
*Mikrokosmos API
*commands: Read by id, Read all, read by date/time

1. Make database
2. go to project settings in firebase site and add "APP"(web app)
3. In project settings go to Service accounts and generate private key -> save private key to projects functions folder with name permissions(otherwise you cant make calls to firebase) 
4. firebase init --> npm i express --> npm i cors
5. Start local webserver by writing command on console(remember cd functions): npm run serve
6. develope

*/

//Parameters
const functions = require('firebase-functions');
const admin = require('firebase-admin');
var serviceAccount = require("./permissions.json");

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://amiable-hydra-279814.firebaseio.com"
});

const express = require('express');
const mikrokosmos = express();
const db = admin.firestore();

const cors = require('cors');
mikrokosmos.use(cors({origin:true}));

//Read a specific item from database with ID
mikrokosmos.get('/api/read/:id',(req,res)=>{
    (async()=>{
        try{
            const document = db.collection('Mikrokosmos-6-11-2020').doc(req.params.id);
            let sensorReading = await document.get();
            let response =sensorReading.data();

            return res.status(200).send(response);
        }catch(error){
            console.log(error);
            return res.status(500).send(error);
        }
    })();
});

//Read all items
mikrokosmos.get('/api/read',(req,res)=>{
    (async()=>{
        try{
            let query = db.collection('Mikrokosmos-6-11-2020');
            let response=[];          

            //Get all data from firebase with query
            await query.get().then(querySnapshot=>{
                let docs = querySnapshot.docs;
                
                for (let doc of docs)
                {
                    const selectedItem={
                        id: doc.id,
                        name:doc.data().name,
                        data: doc.data().data,
                        publishTime: doc.data().publishTime
                    };
                    response.push(selectedItem);
                }
                return response;
            })
            //Make sorted list(New>Old)
            const sortedResponse = response.sort((a, b) => new Date(b.data.time) - new Date(a.data.time)); //Sort list              
            return res.status(200).send(sortedResponse);

        }catch(error){
            console.log(error);
            return res.status(500).send(error);
        }
    })();
});

//Get by date or time
mikrokosmos.get('/api/read/datetime/:day',(req,res)=>{
    (async()=>{
        try{
            let query = db.collection('Mikrokosmos-6-11-2020');
            let response=[];
            let compareList=[];
            console.log("TRY");
            await query.get().then(querySnapshot=>{
                let docs = querySnapshot.docs;
                console.log("AWAIT");
                
                for (let doc of docs)
                {
                    const selectedItem={
                        id: doc.id,
                        name:doc.data().name,
                        data: doc.data().data,
                        publishTime: doc.data().publishTime
                    };

                    //make deep copy from selectedItem and filter seconds from the time
                    var copySelectedItem=JSON.parse(JSON.stringify(selectedItem));
                    var responseSplit=copySelectedItem.data.time.split(':');
                    copySelectedItem.data.time=responseSplit.slice(0,-1).join(':');

                    compareList.push(copySelectedItem);
                    response.push(selectedItem);
                }
                return response;
            })

            let dayList=[];          
            //If value time parameter has included string add it to dayList. Using compareList variable to avoid problems when user searches with hh:mm.
            for(var i in compareList) { 
                if(compareList[i].data.time.includes(req.params.day)){
                    dayList.push(response[i]);
                }
            }
            //Sort daylist(new>old)
            dayList = dayList.sort((a, b) => new Date(b.data.time) - new Date(a.data.time));                        
            return res.status(200).send(dayList);

        }catch(error){
            console.log(error);
            return res.status(500).send(error);
        }
    })();
});

exports.mikrokosmos= functions.https.onRequest(mikrokosmos);

