var admin = require('firebase-admin');

admin.initializeApp({
  credentials: admin.credential.applicationDefault()
});

var db = admin.firestore();

exports.helloPubSub = (event, context) => {

  const pubsubMsg = event;

  //Data variable from particle. Need to be parsed because variable is in JSON format
  var dataToFirestore = Buffer.from(pubsubMsg.data, 'base64').toString();
  var dataToFirestoreJSON=JSON.parse(dataToFirestore)

  var publishTime = pubsubMsg.attributes.published_at;
  var deviceName = pubsubMsg.attributes.event;

  //Firebase collection where data is pushed
  var docRef = db.collection('Mikrokosmos-6-11-2020');

  //data to input on collection
  var setData = docRef.add({
    data:dataToFirestoreJSON,
    publishTime:publishTime,
    name:deviceName

  });

  return null
};
