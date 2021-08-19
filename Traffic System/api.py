# Using flask to make an api
# import necessary libraries and functions
from flask import Flask, json, jsonify, request
import flask
import os
from flask_cors import CORS
  
# creating a Flask app
app = Flask(__name__)


def run_algorithm(json_data):
    var = os.system("g++ dqtrr.cpp -o check")
    command = './check ' + str(json_data["west_left"]) + ' ' + str(json_data["west_right"])+ ' ' + str(json_data["west_straight"])+ ' ' + str(json_data["west_uturn"])+ ' ' + str(json_data["east_left"])+ ' ' + str(json_data["east_right"])+ ' ' + str(json_data["east_straight"])+ ' ' + str(json_data["east_uturn"])+ ' ' + str(json_data["north_left"])+ ' ' + str(json_data["north_right"])+ ' ' + str(json_data["north_straight"])+ ' ' + str(json_data["north_uturn"])+ ' ' + str(json_data["south_left"])+ ' ' + str(json_data["south_right"])+ ' ' + str(json_data["south_straight"])+ ' ' + str(json_data["south_uturn"])
    if var is 0:
        os.system(command)
        file = open("output.json", 'r')
        data = json.load(file)
        os.system("rm check")
        return data
    else:
        return "Issue with the algorithm"
  
# on the terminal type: curl http://127.0.0.1:5000/
# returns hello world when we use GET.
# returns the data that we send when we use POST.
@app.route('/', methods = ['GET', 'POST'])
def home():
    data = "Traffic Worker works!!!"
    return jsonify({'data': data})
  
  
#api to send the input traffic values and get state timeline of the traffic signals
@app.route('/traffic-enable', methods = ['POST'])
def get_traffic_states():
    json_data = flask.request.json
    print("#############################")
    print(json_data)
    print("#############################")
    return_value = run_algorithm(json_data)
    if(isinstance(return_value, str) is False):
        return_value = jsonify(return_value)
    return return_value
  

if __name__ == '__main__':
    CORS(app)
    app.run(debug = True)