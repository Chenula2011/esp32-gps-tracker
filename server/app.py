from flask import Flask, request, jsonify
import requests

app = Flask(__name__)

@app.route('/get_address')
def get_address():
    # Get GPS coordinates from ESP32
    lat = request.args.get('lat')
    lon = request.args.get('lon')
    
    # Convert to Sinhala address
    osm_url = f"https://nominatim.openstreetmap.org/reverse?lat={lat}&lon={lon}&format=json&accept-language=si"
    response = requests.get(osm_url).json()
    
    return jsonify({
        "address": response.get("display_name", "Location not found")
    })

if __name__ == '__main__':
    app.run()
