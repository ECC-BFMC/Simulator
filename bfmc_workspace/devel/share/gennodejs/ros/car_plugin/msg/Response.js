// Auto-generated. Do not edit!

// (in-package car_plugin.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Key = require('./Key.js');

//-----------------------------------------------------------

class Response {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.key = null;
      this.response = null;
    }
    else {
      if (initObj.hasOwnProperty('key')) {
        this.key = initObj.key
      }
      else {
        this.key = new Key();
      }
      if (initObj.hasOwnProperty('response')) {
        this.response = initObj.response
      }
      else {
        this.response = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Response
    // Serialize message field [key]
    bufferOffset = Key.serialize(obj.key, buffer, bufferOffset);
    // Serialize message field [response]
    bufferOffset = _serializer.string(obj.response, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Response
    let len;
    let data = new Response(null);
    // Deserialize message field [key]
    data.key = Key.deserialize(buffer, bufferOffset);
    // Deserialize message field [response]
    data.response = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.response.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_plugin/Response';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '62068c192be1c92f944918b622366c47';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Key key
    string response
    ================================================================================
    MSG: car_plugin/Key
    # Message constabt field to describe the key values
    uint8 UNKNOWN=0
    uint8 MOVE=1
    uint8 BRAKE=2
    # Message field 
    uint8 v
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Response(null);
    if (msg.key !== undefined) {
      resolved.key = Key.Resolve(msg.key)
    }
    else {
      resolved.key = new Key()
    }

    if (msg.response !== undefined) {
      resolved.response = msg.response;
    }
    else {
      resolved.response = ''
    }

    return resolved;
    }
};

module.exports = Response;
