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

class Command {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.key = null;
      this.msg_val = null;
    }
    else {
      if (initObj.hasOwnProperty('key')) {
        this.key = initObj.key
      }
      else {
        this.key = new Key();
      }
      if (initObj.hasOwnProperty('msg_val')) {
        this.msg_val = initObj.msg_val
      }
      else {
        this.msg_val = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Command
    // Serialize message field [key]
    bufferOffset = Key.serialize(obj.key, buffer, bufferOffset);
    // Serialize message field [msg_val]
    bufferOffset = _arraySerializer.float32(obj.msg_val, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Command
    let len;
    let data = new Command(null);
    // Deserialize message field [key]
    data.key = Key.deserialize(buffer, bufferOffset);
    // Deserialize message field [msg_val]
    data.msg_val = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.msg_val.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_plugin/Command';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e127791eeae9498f8888358c49884e30';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Key key
    float32[] msg_val
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
    const resolved = new Command(null);
    if (msg.key !== undefined) {
      resolved.key = Key.Resolve(msg.key)
    }
    else {
      resolved.key = new Key()
    }

    if (msg.msg_val !== undefined) {
      resolved.msg_val = msg.msg_val;
    }
    else {
      resolved.msg_val = []
    }

    return resolved;
    }
};

module.exports = Command;
