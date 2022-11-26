import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('risinghopper-930d7-firebase-adminsdk-9mmm1-4f43974aae.json')

# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://risinghopper-930d7-default-rtdb.asia-southeast1.firebasedatabase.app/'
})

# As an admin, the app has access to read and write all data, regradless of Security Rules
ref = db.reference('')


posts_ref = ref.child('User/-NHmbxhFPwfwFw6dT6Et')

#posts_ref.set()

new_post_ref = posts_ref.push()

posts_ref.child('gracehop').update({
    'nickname': 'Power Amazing Gracehop123'
})


Hopper = ref.child('Hopper')
Hopper.delete()