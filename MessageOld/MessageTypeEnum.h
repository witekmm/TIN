#IFNDEF MESSAGE_TYPE_ENUM_H
#DEFINE MESSAGE_TYPE_ENUM_H

enum MessageType: int32_t{
  message = 0,
  command = 1,
  login = 2,
  password = 3,
  group_create = 4,
  group_delete = 5,
  group_request = 6,
  group_accept = 7,
  group_decline = 8,
};

#ENDIF
