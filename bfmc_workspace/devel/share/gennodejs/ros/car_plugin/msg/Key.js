// Auto-generated. Do not edit!

// (in-package car_plugin.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Key {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.v = null;
    }
    else {
      if (initObj.hasOwnProperty('v')) {
        this.v = initObj.v
      }
      else {
        this.v = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Key
    // Serialize message field [v]
    bufferOffset = _serializer.uint8(obj.v, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Key
    let len;
    let data = new Key(null);
    // Deserialize message field [v]
    data.v = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'car_plugin/Key';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e0ea58642b36fae1b5437fc7c2183bed';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Key(null);
    if (msg.v !== undefined) {
      resolved.v = msg.v;
    }
    else {
      resolved.v = 0
    }

    return resolved;
    }
};

// Constants for message
Key.Constants = {
  UNKNOWN: 0,
  MOVE: 1,
  BRAKE: 2,
}

module.exports = Key;
