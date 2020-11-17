# Google Cloud Functions
These files have the code of google cloud functions used to store data. Each function is triggered always after pub/sub event occurs(when particle sends data to GCP).

### DataToFirestore (js8)
- Saves data from Particle to firestore/firebase collection.
### DataToGoogleSheet (python)
- Writes data from particle to predefined google sheet file
