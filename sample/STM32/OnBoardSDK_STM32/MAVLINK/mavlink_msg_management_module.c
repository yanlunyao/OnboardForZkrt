// MESSAGE STATUSTEXT PACKING

#include "mavlink_msg_management_module.h"
/**
 * @brief Pack a statustext message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param severity Severity of status. Relies on the definitions within RFC-5424. See enum MAV_SEVERITY.
 * @param text Status text message, without null termination character
 * @return length of the message in bytes (excluding serial stream start sign)
 */


uint16_t mavlink_msg_management_module_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const char *in_packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_STATUSTEXT_LEN];
	_mav_put_uint8_t(buf, 0, severity);
	_mav_put_char_array(buf, 1, text, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATUSTEXT_LEN);
#else
	mavlink_management_module_t packet;
	mav_array_memcpy((void *)&packet.zkrt_packet, in_packet, sizeof(char)*50);
  memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MANGEMENT_MODULE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN, MAVLINK_MSG_ID_MANGEMENT_MODULE_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN);
#endif
}

/**
 * @brief Pack a statustext message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param severity Severity of status. Relies on the definitions within RFC-5424. See enum MAV_SEVERITY.
 * @param text Status text message, without null termination character
 * @return length of the message in bytes (excluding serial stream start sign)
 */
uint16_t mavlink_msg_management_module_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,mavlink_message_t* msg,const char *in_packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_STATUSTEXT_LEN];
	_mav_put_uint8_t(buf, 0, severity);
	_mav_put_char_array(buf, 1, text, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATUSTEXT_LEN);
#else
	mavlink_management_module_t packet;
	mav_array_memcpy((void *)&packet.zkrt_packet, in_packet, sizeof(char)*50);
  memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_MANGEMENT_MODULE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN, MAVLINK_MSG_ID_MANGEMENT_MODULE_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STATUSTEXT_LEN);
#endif
}

/**
 * @brief Encode a statustext struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param statustext C-struct to read the message contents from
 */
uint16_t mavlink_msg_management_module_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_management_module_t* managementmodule)
{
	return mavlink_msg_management_module_pack(system_id, component_id, msg, (char *)&managementmodule->zkrt_packet);
}

/**
 * @brief Encode a statustext struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param statustext C-struct to read the message contents from
 */
uint16_t mavlink_msg_management_module_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_management_module_t* mangementmodule)
{
	return mavlink_msg_management_module_pack_chan(system_id, component_id, chan, msg, (char *)&mangementmodule->zkrt_packet);
}

/**
 * @brief Send a statustext message
 * @param chan MAVLink channel to send the message
 *
 * @param severity Severity of status. Relies on the definitions within RFC-5424. See enum MAV_SEVERITY.
 * @param text Status text message, without null termination character
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

void mavlink_msg_management_module_send(mavlink_channel_t chan,  const char *in_packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_STATUSTEXT_LEN];
	_mav_put_uint8_t(buf, 0, severity);
	_mav_put_char_array(buf, 1, text, 50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATUSTEXT, buf, MAVLINK_MSG_ID_STATUSTEXT_LEN, MAVLINK_MSG_ID_STATUSTEXT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATUSTEXT, buf, MAVLINK_MSG_ID_STATUSTEXT_LEN);
#endif
#else
	mavlink_management_module_t packet;
	mav_array_memcpy((void *)&packet.zkrt_packet, in_packet, sizeof(char)*50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MANGEMENT_MODULE, (const char *)&packet, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN, MAVLINK_MSG_ID_MANGEMENT_MODULE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATUSTEXT, (const char *)&packet, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_STATUSTEXT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
void mavlink_msg_management_module_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan, const char *in_packet)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, severity);
	_mav_put_char_array(buf, 1, text, 50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATUSTEXT, buf, MAVLINK_MSG_ID_STATUSTEXT_LEN, MAVLINK_MSG_ID_STATUSTEXT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATUSTEXT, buf, MAVLINK_MSG_ID_STATUSTEXT_LEN);
#endif
#else
	mavlink_management_module_t *packet = (mavlink_management_module_t *)msgbuf;
	mav_array_memcpy((void *)&packet->zkrt_packet, in_packet, sizeof(char)*50);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MANGEMENT_MODULE, (const char *)packet, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN, MAVLINK_MSG_ID_MANGEMENT_MODULE_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATUSTEXT, (const char *)packet, MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE STATUSTEXT UNPACKING


/**
 * @brief Get field severity from statustext message
 *
 * @return Severity of status. Relies on the definitions within RFC-5424. See enum MAV_SEVERITY.
 */
uint8_t mavlink_msg_management_module_get_severity(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field text from statustext message
 *
 * @return Status text message, without null termination character
 */
uint16_t mavlink_msg_management_module_get_text(const mavlink_message_t* msg, char *in_packet)
{
	return _MAV_RETURN_char_array(msg, in_packet, 50,  1);
}

/**
 * @brief Decode a statustext message into a struct
 *
 * @param msg The message to decode
 * @param statustext C-struct to decode the message contents into
 */
void mavlink_msg_management_module_decode(const mavlink_message_t* msg, mavlink_management_module_t* mangementmodule)
{
#if MAVLINK_NEED_BYTE_SWAP
	statustext->severity = mavlink_msg_statustext_get_severity(msg);
	mavlink_msg_statustext_get_text(msg, statustext->text);
#else
	memcpy(mangementmodule, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_MANGEMENT_MODULE_LEN);
#endif
}
