// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Message.proto

#include "Message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace Message {
class ClientMessageDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ClientMessage> _instance;
} _ClientMessage_default_instance_;
}  // namespace Message
static void InitDefaultsClientMessage_Message_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Message::_ClientMessage_default_instance_;
    new (ptr) ::Message::ClientMessage();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Message::ClientMessage::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_ClientMessage_Message_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsClientMessage_Message_2eproto}, {}};

void InitDefaults_Message_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_ClientMessage_Message_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_Message_2eproto[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors_Message_2eproto[1];
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_Message_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_Message_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::Message::ClientMessage, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::Message::ClientMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Message::ClientMessage, type_),
  PROTOBUF_FIELD_OFFSET(::Message::ClientMessage, start_),
  PROTOBUF_FIELD_OFFSET(::Message::ClientMessage, destination_),
  PROTOBUF_FIELD_OFFSET(::Message::ClientMessage, content_),
  1,
  2,
  3,
  0,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, sizeof(::Message::ClientMessage)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::Message::_ClientMessage_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_Message_2eproto = {
  {}, AddDescriptors_Message_2eproto, "Message.proto", schemas,
  file_default_instances, TableStruct_Message_2eproto::offsets,
  file_level_metadata_Message_2eproto, 1, file_level_enum_descriptors_Message_2eproto, file_level_service_descriptors_Message_2eproto,
};

const char descriptor_table_protodef_Message_2eproto[] =
  "\n\rMessage.proto\022\007Message\"\305\001\n\rClientMessa"
  "ge\0225\n\004type\030\001 \002(\0162\".Message.ClientMessage"
  ".messageType:\003MSG\022\r\n\005start\030\002 \001(\005\022\023\n\013dest"
  "ination\030\003 \001(\005\022\017\n\007content\030\004 \001(\t\"H\n\013messag"
  "eType\022\007\n\003MSG\020\000\022\013\n\007COMMAND\020\001\022\020\n\014GROUP_ACC"
  "EPT\020\002\022\021\n\rGROUP_DECLINE\020\003"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_Message_2eproto = {
  false, InitDefaults_Message_2eproto, 
  descriptor_table_protodef_Message_2eproto,
  "Message.proto", &assign_descriptors_table_Message_2eproto, 224,
};

void AddDescriptors_Message_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_Message_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Message_2eproto = []() { AddDescriptors_Message_2eproto(); return true; }();
namespace Message {
const ::google::protobuf::EnumDescriptor* ClientMessage_messageType_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&assign_descriptors_table_Message_2eproto);
  return file_level_enum_descriptors_Message_2eproto[0];
}
bool ClientMessage_messageType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const ClientMessage_messageType ClientMessage::MSG;
const ClientMessage_messageType ClientMessage::COMMAND;
const ClientMessage_messageType ClientMessage::GROUP_ACCEPT;
const ClientMessage_messageType ClientMessage::GROUP_DECLINE;
const ClientMessage_messageType ClientMessage::messageType_MIN;
const ClientMessage_messageType ClientMessage::messageType_MAX;
const int ClientMessage::messageType_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

void ClientMessage::InitAsDefaultInstance() {
}
class ClientMessage::HasBitSetters {
 public:
  static void set_has_type(ClientMessage* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
  static void set_has_start(ClientMessage* msg) {
    msg->_has_bits_[0] |= 0x00000004u;
  }
  static void set_has_destination(ClientMessage* msg) {
    msg->_has_bits_[0] |= 0x00000008u;
  }
  static void set_has_content(ClientMessage* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ClientMessage::kTypeFieldNumber;
const int ClientMessage::kStartFieldNumber;
const int ClientMessage::kDestinationFieldNumber;
const int ClientMessage::kContentFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ClientMessage::ClientMessage()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Message.ClientMessage)
}
ClientMessage::ClientMessage(const ClientMessage& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_content()) {
    content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
  }
  ::memcpy(&type_, &from.type_,
    static_cast<size_t>(reinterpret_cast<char*>(&destination_) -
    reinterpret_cast<char*>(&type_)) + sizeof(destination_));
  // @@protoc_insertion_point(copy_constructor:Message.ClientMessage)
}

void ClientMessage::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_ClientMessage_Message_2eproto.base);
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&type_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&destination_) -
      reinterpret_cast<char*>(&type_)) + sizeof(destination_));
}

ClientMessage::~ClientMessage() {
  // @@protoc_insertion_point(destructor:Message.ClientMessage)
  SharedDtor();
}

void ClientMessage::SharedDtor() {
  content_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void ClientMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ClientMessage& ClientMessage::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_ClientMessage_Message_2eproto.base);
  return *internal_default_instance();
}


void ClientMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:Message.ClientMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    content_.ClearNonDefaultToEmptyNoArena();
  }
  if (cached_has_bits & 0x0000000eu) {
    ::memset(&type_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&destination_) -
        reinterpret_cast<char*>(&type_)) + sizeof(destination_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ClientMessage::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<ClientMessage*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // required .Message.ClientMessage.messageType type = 1 [default = MSG];
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        ::google::protobuf::uint64 val = ::google::protobuf::internal::ReadVarint(&ptr);
        if (!::Message::ClientMessage_messageType_IsValid(val)) {
          ::google::protobuf::internal::WriteVarint(1, val, msg->mutable_unknown_fields());
          break;
        }
        msg->set_type(static_cast<::Message::ClientMessage_messageType>(val));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // optional int32 start = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        msg->set_start(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // optional int32 destination = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        msg->set_destination(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // optional string content = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 34) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName("Message.ClientMessage.content");
        object = msg->mutable_content();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8Verify;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8Verify(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool ClientMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Message.ClientMessage)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .Message.ClientMessage.messageType type = 1 [default = MSG];
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          int value = 0;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::Message::ClientMessage_messageType_IsValid(value)) {
            set_type(static_cast< ::Message::ClientMessage_messageType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                1, static_cast<::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 start = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {
          HasBitSetters::set_has_start(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &start_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 destination = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {
          HasBitSetters::set_has_destination(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &destination_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string content = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (34 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->content().data(), static_cast<int>(this->content().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "Message.ClientMessage.content");
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Message.ClientMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Message.ClientMessage)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ClientMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Message.ClientMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .Message.ClientMessage.messageType type = 1 [default = MSG];
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }

  // optional int32 start = 2;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->start(), output);
  }

  // optional int32 destination = 3;
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->destination(), output);
  }

  // optional string content = 4;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->content().data(), static_cast<int>(this->content().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "Message.ClientMessage.content");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->content(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Message.ClientMessage)
}

::google::protobuf::uint8* ClientMessage::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Message.ClientMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .Message.ClientMessage.messageType type = 1 [default = MSG];
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->type(), target);
  }

  // optional int32 start = 2;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->start(), target);
  }

  // optional int32 destination = 3;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->destination(), target);
  }

  // optional string content = 4;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->content().data(), static_cast<int>(this->content().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "Message.ClientMessage.content");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->content(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Message.ClientMessage)
  return target;
}

size_t ClientMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Message.ClientMessage)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  // required .Message.ClientMessage.messageType type = 1 [default = MSG];
  if (has_type()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional string content = 4;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->content());
  }

  if (cached_has_bits & 0x0000000cu) {
    // optional int32 start = 2;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->start());
    }

    // optional int32 destination = 3;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->destination());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ClientMessage::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Message.ClientMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const ClientMessage* source =
      ::google::protobuf::DynamicCastToGenerated<ClientMessage>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Message.ClientMessage)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Message.ClientMessage)
    MergeFrom(*source);
  }
}

void ClientMessage::MergeFrom(const ClientMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Message.ClientMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
    }
    if (cached_has_bits & 0x00000002u) {
      type_ = from.type_;
    }
    if (cached_has_bits & 0x00000004u) {
      start_ = from.start_;
    }
    if (cached_has_bits & 0x00000008u) {
      destination_ = from.destination_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void ClientMessage::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Message.ClientMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ClientMessage::CopyFrom(const ClientMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Message.ClientMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClientMessage::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;
  return true;
}

void ClientMessage::Swap(ClientMessage* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ClientMessage::InternalSwap(ClientMessage* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  content_.Swap(&other->content_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(type_, other->type_);
  swap(start_, other->start_);
  swap(destination_, other->destination_);
}

::google::protobuf::Metadata ClientMessage::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_Message_2eproto);
  return ::file_level_metadata_Message_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Message
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::Message::ClientMessage* Arena::CreateMaybeMessage< ::Message::ClientMessage >(Arena* arena) {
  return Arena::CreateInternal< ::Message::ClientMessage >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>