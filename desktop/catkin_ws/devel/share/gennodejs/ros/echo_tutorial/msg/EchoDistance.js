// Auto-generated. Do not edit!

// (in-package echo_tutorial.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class EchoDistance {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Stamp = null;
      this.Distance = null;
    }
    else {
      if (initObj.hasOwnProperty('Stamp')) {
        this.Stamp = initObj.Stamp
      }
      else {
        this.Stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('Distance')) {
        this.Distance = initObj.Distance
      }
      else {
        this.Distance = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type EchoDistance
    // Serialize message field [Stamp]
    bufferOffset = _serializer.time(obj.Stamp, buffer, bufferOffset);
    // Serialize message field [Distance]
    bufferOffset = _serializer.float64(obj.Distance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type EchoDistance
    let len;
    let data = new EchoDistance(null);
    // Deserialize message field [Stamp]
    data.Stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [Distance]
    data.Distance = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'echo_tutorial/EchoDistance';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd7755fc5d2735bcfbf5a864c13aab9ab';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time Stamp
    float64 Distance
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new EchoDistance(null);
    if (msg.Stamp !== undefined) {
      resolved.Stamp = msg.Stamp;
    }
    else {
      resolved.Stamp = {secs: 0, nsecs: 0}
    }

    if (msg.Distance !== undefined) {
      resolved.Distance = msg.Distance;
    }
    else {
      resolved.Distance = 0.0
    }

    return resolved;
    }
};

module.exports = EchoDistance;
