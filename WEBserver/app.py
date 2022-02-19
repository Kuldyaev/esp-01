from flask import Flask, request, jsonify
from datetime import datetime
from flask_sqlalchemy import SQLAlchemy
from flask_cors import CORS, cross_origin
import os


basedir = os.path.abspath(os.path.dirname(__file__))

app=Flask(__name__)
CORS(app)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'server.db')
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

db.metadata.clear()

class Measurements(db.Model):
       __tablename__='measurements'
       meas_id = db.Column(db.Integer, primary_key=True)
       meas_botname = db.Column(db.String(10), nullable=False)
       meas_time = db.Column(db.DateTime(), default=datetime.utcnow)
       meas_tempA = db.Column(db.Float)
       meas_humA  = db.Column(db.Float)
       meas_light = db.Column(db.Integer)
       meas_tempDallas = db.Column(db.Float)
       meas_tempB = db.Column(db.Float)
       meas_pressB = db.Column(db.Integer)
       def __repr__(self):
           return '<Measurements %r>' % self.meas_id

db.create_all() 

@app.route("/")
def hello_world():
    print("mainPageVisited")
    return "<h1>Hi!</h1>"

@app.route("/meas", methods=['GET','POST'])
def measurements():
    if request.method=='POST':
        if request.is_json:
            data = request.get_json()
            datadata = data['data']
            print(data)
            newMeas =  Measurements(meas_botname=data['bot'],
                       meas_tempA=float(datadata['tempAM2320']),
                       meas_humA=float(datadata['humAM2320']),
                       meas_light=int(datadata['lightA']),
                       meas_tempDallas=float(datadata['tempDallas']),
                       meas_tempB=float(datadata['tempBMP180']),
                       meas_pressB=int(datadata['presBMP180'])) 
            try:
                db.session.add(newMeas)
                db.session.commit()
                print("all doog")
                return "OK"
            except:
                print('Something was wrong')
                return "NotGood"
    else:
        return "<p>Get</p>"

if __name__=='__main__':
    app.run(debug=True, host='0.0.0.0', port=8833)

