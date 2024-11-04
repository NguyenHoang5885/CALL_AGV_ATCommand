#code flask
from flask import Flask, request, jsonify

# Khởi tạo Flask
app = Flask(__name__)

@app.route('/items', methods=['POST'])
def create_item():
    try:
    # Lấy dữ liệu JSON 
        data = request.get_json()
        print(data)
        # Xử lý dữ liệu 
        item_name = data.get('name')
        item_Value = data.get('Value')

        # Trả về dữ liệu dưới dạng JSON
        response = {
            'message': 'Item created successfully',
            'item': {
                'name': item_name, 
                'Value': item_Value
            }
        }
        return jsonify(response), 200  
    except Exception as e :
        print(e)
        response = {
            'message': e
        }
        return jsonify(response), 400 

@app.route('/api/hello', methods=['GET'])
def hello():
    try:
        response = {"a" : "123"}
        return jsonify(response), 200 
    except Exception as e :
        print(e)
        response = {
            'message': e
        }
        return jsonify(response), 400
if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0", port=5000)
