// Auto-generated. Do not edit!

// (in-package led_tutorial.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetRGBDigitalRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.R = null;
      this.G = null;
      this.B = null;
    }
    else {
      if (initObj.hasOwnProperty('R')) {
        this.R = initObj.R
      }
      else {
        this.R = false;
      }
      if (initObj.hasOwnProperty('G')) {
        this.G = initObj.G
      }
      else {
        this.G = false;
      }
      if (initObj.hasOwnProperty('B')) {
        this.B = initObj.B
      }
      else {
        this.B = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetRGBDigitalRequest
    // Serialize message field [R]
    bufferOffset = _serializer.bool(obj.R, buffer, bufferOffset);
    // Serialize message field [G]
    bufferOffset = _serializer.bool(obj.G, buffer, bufferOffset);
    // Serialize message field [B]
    bufferOffset = _serializer.bool(obj.B, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetRGBDigitalRequest
    let len;
    let data = new SetRGBDigitalRequest(null);
    // Deserialize message field [R]
    data.R = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [G]
    data.G = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [B]
    data.B = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 3;
  }

  static datatype() {
    // Returns string type for a service object
    return 'led_tutorial/SetRGBDigitalRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8d9ee9a10b4c93855d8d93f386df8a93';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool R
    bool G
    bool B
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetRGBDigitalRequest(null);
    if (msg.R !== undefined) {
      resolved.R = msg.R;
    }
    else {
      resolved.R = false
    }

    if (msg.G !== undefined) {
      resolved.G = msg.G;
    }
    else {
      resolved.G = false
    }

    if (msg.B !== undefined) {
      resolved.B = msg.B;
    }
    else {
      resolved.B = false
    }

    return resolved;
    }
};

class SetRGBDigitalResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.result = null;
      this.message = null;
      this.Timestamp = null;
    }
    else {
      if (initObj.hasOwnProperty('result')) {
        this.result = initObj.result
      }
      else {
        this.result = '';
      }
      if (initObj.hasOwnProperty('message')) {
        this.message = initObj.message
      }
      else {
        this.message = '';
      }
      if (initObj.hasOwnProperty('Timestamp')) {
        this.Timestamp = initObj.Timestamp
      }
      else {
        this.Timestamp = {secs: 0, nsecs: 0};
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetRGBDigitalResponse
    // Serialize message field [result]
    bufferOffset = _serializer.string(obj.result, buffer, bufferOffset);
    // Serialize message field [message]
    bufferOffset = _serializer.string(obj.message, buffer, bufferOffset);
    // Serialize message field [Timestamp]
    bufferOffset = _serializer.time(obj.Timestamp, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetRGBDigitalResponse
    let len;
    let data = new SetRGBDigitalResponse(null);
    // Deserialize message field [result]
    data.result = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [message]
    data.message = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [Timestamp]
    data.Timestamp = _deserializer.time(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.result);
    length += _getByteLength(object.message);
    return length + 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'led_tutorial/SetRGBDigitalResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ad1c7d9d0ff8ca871b1c881c758f3f9b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string result
    string message
    time   Timestamp
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetRGBDigitalResponse(null);
    if (msg.result !== undefined) {
      resolved.result = msg.result;
    }
    else {
      resolved.result = ''
    }

    if (msg.message !== undefined) {
      resolved.message = msg.message;
    }
    else {
      resolved.message = ''
    }

    if (msg.Timestamp !== undefined) {
      resolved.Timestamp = msg.Timestamp;
    }
    else {
      resolved.Timestamp = {secs: 0, nsecs: 0}
    }

    return resolved;
    }
};

module.exports = {
  Request: SetRGBDigitalRequest,
  Response: SetRGBDigitalResponse,
  md5sum() { return '9df6cef7d28f2f7dca06723b950a75f7'; },
  datatype() { return 'led_tutorial/SetRGBDigital'; }
};
