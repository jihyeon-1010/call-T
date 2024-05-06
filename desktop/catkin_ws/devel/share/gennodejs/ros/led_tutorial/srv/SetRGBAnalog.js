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

class SetRGBAnalogRequest {
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
        this.R = 0;
      }
      if (initObj.hasOwnProperty('G')) {
        this.G = initObj.G
      }
      else {
        this.G = 0;
      }
      if (initObj.hasOwnProperty('B')) {
        this.B = initObj.B
      }
      else {
        this.B = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetRGBAnalogRequest
    // Serialize message field [R]
    bufferOffset = _serializer.uint8(obj.R, buffer, bufferOffset);
    // Serialize message field [G]
    bufferOffset = _serializer.uint8(obj.G, buffer, bufferOffset);
    // Serialize message field [B]
    bufferOffset = _serializer.uint8(obj.B, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetRGBAnalogRequest
    let len;
    let data = new SetRGBAnalogRequest(null);
    // Deserialize message field [R]
    data.R = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [G]
    data.G = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [B]
    data.B = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 3;
  }

  static datatype() {
    // Returns string type for a service object
    return 'led_tutorial/SetRGBAnalogRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '25e8e0a5fcebfd5489b6ec59d3303e32';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 R
    uint8 G
    uint8 B
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetRGBAnalogRequest(null);
    if (msg.R !== undefined) {
      resolved.R = msg.R;
    }
    else {
      resolved.R = 0
    }

    if (msg.G !== undefined) {
      resolved.G = msg.G;
    }
    else {
      resolved.G = 0
    }

    if (msg.B !== undefined) {
      resolved.B = msg.B;
    }
    else {
      resolved.B = 0
    }

    return resolved;
    }
};

class SetRGBAnalogResponse {
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
    // Serializes a message object of type SetRGBAnalogResponse
    // Serialize message field [result]
    bufferOffset = _serializer.string(obj.result, buffer, bufferOffset);
    // Serialize message field [message]
    bufferOffset = _serializer.string(obj.message, buffer, bufferOffset);
    // Serialize message field [Timestamp]
    bufferOffset = _serializer.time(obj.Timestamp, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetRGBAnalogResponse
    let len;
    let data = new SetRGBAnalogResponse(null);
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
    return 'led_tutorial/SetRGBAnalogResponse';
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
    const resolved = new SetRGBAnalogResponse(null);
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
  Request: SetRGBAnalogRequest,
  Response: SetRGBAnalogResponse,
  md5sum() { return 'e9c8c842901f7001b386259a45987503'; },
  datatype() { return 'led_tutorial/SetRGBAnalog'; }
};
