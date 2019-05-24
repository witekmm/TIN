// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: Message.proto
// </auto-generated>
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace Message {

  /// <summary>Holder for reflection information generated from Message.proto</summary>
  public static partial class MessageReflection {

    #region Descriptor
    /// <summary>File descriptor for Message.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static MessageReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "Cg1NZXNzYWdlLnByb3RvEgdNZXNzYWdlIoYGCg1DbGllbnRNZXNzYWdlEjgK",
            "C21lc3NhZ2VUeXBlGAEgASgOMiMuTWVzc2FnZS5DbGllbnRNZXNzYWdlLm1l",
            "c3NhZ2VUeXBlcxJACg9ncm91cEFjdGlvblR5cGUYAiABKA4yJy5NZXNzYWdl",
            "LkNsaWVudE1lc3NhZ2UuZ3JvdXBBY3Rpb25UeXBlcxJEChFhdXRob3JpemF0",
            "aW9uVHlwZRgDIAEoDjIpLk1lc3NhZ2UuQ2xpZW50TWVzc2FnZS5hdXRob3Jp",
            "emF0aW9uVHlwZXMSOAoLY29tbWFuZFR5cGUYBCABKA4yIy5NZXNzYWdlLkNs",
            "aWVudE1lc3NhZ2UuY29tbWFuZFR5cGVzEg0KBWxvZ2luGAUgASgJEhAKCHBh",
            "c3N3b3JkGAYgASgJEhEKCWdyb3VwTmFtZRgHIAEoCRIQCgh1c2VyTmFtZRgI",
            "IAEoCRIWCg5tZXNzYWdlQ29udGVudBgJIAEoCRIxCgVyZXBseRgKIAEoDjIi",
            "Lk1lc3NhZ2UuQ2xpZW50TWVzc2FnZS5yZXBseVN0YXR1cxIUCgxyZXBseUNv",
            "bnRlbnQYCyABKAkSDgoGZ3JvdXBzGAwgAygJIjkKDG1lc3NhZ2VUeXBlcxIR",
            "Cg1BVVRIT1JJWkFUSU9OEAASCwoHQ09NTUFORBABEgkKBUdST1VQEAIiaAoQ",
            "Z3JvdXBBY3Rpb25UeXBlcxILCgdNRVNTQUdFEAASCgoGQ1JFQVRFEAESCgoG",
            "REVMRVRFEAISCwoHUkVRVUVTVBADEgoKBkFDQ0VQVBAEEgsKB0RFQ0xJTkUQ",
            "BRIJCgVMRUFWRRAGIksKEmF1dGhvcml6YXRpb25UeXBlcxIKCgZMT0dfSU4Q",
            "ABISCg5SRUdJU1RFUl9MT0dJThABEhUKEVJFR0lTVEVSX1BBU1NXT1JEEAIi",
            "JQoMY29tbWFuZFR5cGVzEggKBEVYSVQQABILCgdMT0dfT1VUEAEiKQoLcmVw",
            "bHlTdGF0dXMSDAoIUE9TSVRJVkUQABIMCghORUdBVElWRRABYgZwcm90bzM="));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { },
          new pbr::GeneratedClrTypeInfo(null, new pbr::GeneratedClrTypeInfo[] {
            new pbr::GeneratedClrTypeInfo(typeof(global::Message.ClientMessage), global::Message.ClientMessage.Parser, new[]{ "MessageType", "GroupActionType", "AuthorizationType", "CommandType", "Login", "Password", "GroupName", "UserName", "MessageContent", "Reply", "ReplyContent", "Groups" }, null, new[]{ typeof(global::Message.ClientMessage.Types.messageTypes), typeof(global::Message.ClientMessage.Types.groupActionTypes), typeof(global::Message.ClientMessage.Types.authorizationTypes), typeof(global::Message.ClientMessage.Types.commandTypes), typeof(global::Message.ClientMessage.Types.replyStatus) }, null)
          }));
    }
    #endregion

  }
  #region Messages
  public sealed partial class ClientMessage : pb::IMessage<ClientMessage> {
    private static readonly pb::MessageParser<ClientMessage> _parser = new pb::MessageParser<ClientMessage>(() => new ClientMessage());
    private pb::UnknownFieldSet _unknownFields;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pb::MessageParser<ClientMessage> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::Message.MessageReflection.Descriptor.MessageTypes[0]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public ClientMessage() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public ClientMessage(ClientMessage other) : this() {
      messageType_ = other.messageType_;
      groupActionType_ = other.groupActionType_;
      authorizationType_ = other.authorizationType_;
      commandType_ = other.commandType_;
      login_ = other.login_;
      password_ = other.password_;
      groupName_ = other.groupName_;
      userName_ = other.userName_;
      messageContent_ = other.messageContent_;
      reply_ = other.reply_;
      replyContent_ = other.replyContent_;
      groups_ = other.groups_.Clone();
      _unknownFields = pb::UnknownFieldSet.Clone(other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public ClientMessage Clone() {
      return new ClientMessage(this);
    }

    /// <summary>Field number for the "messageType" field.</summary>
    public const int MessageTypeFieldNumber = 1;
    private global::Message.ClientMessage.Types.messageTypes messageType_ = 0;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public global::Message.ClientMessage.Types.messageTypes MessageType {
      get { return messageType_; }
      set {
        messageType_ = value;
      }
    }

    /// <summary>Field number for the "groupActionType" field.</summary>
    public const int GroupActionTypeFieldNumber = 2;
    private global::Message.ClientMessage.Types.groupActionTypes groupActionType_ = 0;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public global::Message.ClientMessage.Types.groupActionTypes GroupActionType {
      get { return groupActionType_; }
      set {
        groupActionType_ = value;
      }
    }

    /// <summary>Field number for the "authorizationType" field.</summary>
    public const int AuthorizationTypeFieldNumber = 3;
    private global::Message.ClientMessage.Types.authorizationTypes authorizationType_ = 0;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public global::Message.ClientMessage.Types.authorizationTypes AuthorizationType {
      get { return authorizationType_; }
      set {
        authorizationType_ = value;
      }
    }

    /// <summary>Field number for the "commandType" field.</summary>
    public const int CommandTypeFieldNumber = 4;
    private global::Message.ClientMessage.Types.commandTypes commandType_ = 0;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public global::Message.ClientMessage.Types.commandTypes CommandType {
      get { return commandType_; }
      set {
        commandType_ = value;
      }
    }

    /// <summary>Field number for the "login" field.</summary>
    public const int LoginFieldNumber = 5;
    private string login_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string Login {
      get { return login_; }
      set {
        login_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "password" field.</summary>
    public const int PasswordFieldNumber = 6;
    private string password_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string Password {
      get { return password_; }
      set {
        password_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "groupName" field.</summary>
    public const int GroupNameFieldNumber = 7;
    private string groupName_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string GroupName {
      get { return groupName_; }
      set {
        groupName_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "userName" field.</summary>
    public const int UserNameFieldNumber = 8;
    private string userName_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string UserName {
      get { return userName_; }
      set {
        userName_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "messageContent" field.</summary>
    public const int MessageContentFieldNumber = 9;
    private string messageContent_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string MessageContent {
      get { return messageContent_; }
      set {
        messageContent_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "reply" field.</summary>
    public const int ReplyFieldNumber = 10;
    private global::Message.ClientMessage.Types.replyStatus reply_ = 0;
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public global::Message.ClientMessage.Types.replyStatus Reply {
      get { return reply_; }
      set {
        reply_ = value;
      }
    }

    /// <summary>Field number for the "replyContent" field.</summary>
    public const int ReplyContentFieldNumber = 11;
    private string replyContent_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string ReplyContent {
      get { return replyContent_; }
      set {
        replyContent_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    /// <summary>Field number for the "groups" field.</summary>
    public const int GroupsFieldNumber = 12;
    private static readonly pb::FieldCodec<string> _repeated_groups_codec
        = pb::FieldCodec.ForString(98);
    private readonly pbc::RepeatedField<string> groups_ = new pbc::RepeatedField<string>();
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public pbc::RepeatedField<string> Groups {
      get { return groups_; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override bool Equals(object other) {
      return Equals(other as ClientMessage);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public bool Equals(ClientMessage other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (MessageType != other.MessageType) return false;
      if (GroupActionType != other.GroupActionType) return false;
      if (AuthorizationType != other.AuthorizationType) return false;
      if (CommandType != other.CommandType) return false;
      if (Login != other.Login) return false;
      if (Password != other.Password) return false;
      if (GroupName != other.GroupName) return false;
      if (UserName != other.UserName) return false;
      if (MessageContent != other.MessageContent) return false;
      if (Reply != other.Reply) return false;
      if (ReplyContent != other.ReplyContent) return false;
      if(!groups_.Equals(other.groups_)) return false;
      return Equals(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override int GetHashCode() {
      int hash = 1;
      if (MessageType != 0) hash ^= MessageType.GetHashCode();
      if (GroupActionType != 0) hash ^= GroupActionType.GetHashCode();
      if (AuthorizationType != 0) hash ^= AuthorizationType.GetHashCode();
      if (CommandType != 0) hash ^= CommandType.GetHashCode();
      if (Login.Length != 0) hash ^= Login.GetHashCode();
      if (Password.Length != 0) hash ^= Password.GetHashCode();
      if (GroupName.Length != 0) hash ^= GroupName.GetHashCode();
      if (UserName.Length != 0) hash ^= UserName.GetHashCode();
      if (MessageContent.Length != 0) hash ^= MessageContent.GetHashCode();
      if (Reply != 0) hash ^= Reply.GetHashCode();
      if (ReplyContent.Length != 0) hash ^= ReplyContent.GetHashCode();
      hash ^= groups_.GetHashCode();
      if (_unknownFields != null) {
        hash ^= _unknownFields.GetHashCode();
      }
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void WriteTo(pb::CodedOutputStream output) {
      if (MessageType != 0) {
        output.WriteRawTag(8);
        output.WriteEnum((int) MessageType);
      }
      if (GroupActionType != 0) {
        output.WriteRawTag(16);
        output.WriteEnum((int) GroupActionType);
      }
      if (AuthorizationType != 0) {
        output.WriteRawTag(24);
        output.WriteEnum((int) AuthorizationType);
      }
      if (CommandType != 0) {
        output.WriteRawTag(32);
        output.WriteEnum((int) CommandType);
      }
      if (Login.Length != 0) {
        output.WriteRawTag(42);
        output.WriteString(Login);
      }
      if (Password.Length != 0) {
        output.WriteRawTag(50);
        output.WriteString(Password);
      }
      if (GroupName.Length != 0) {
        output.WriteRawTag(58);
        output.WriteString(GroupName);
      }
      if (UserName.Length != 0) {
        output.WriteRawTag(66);
        output.WriteString(UserName);
      }
      if (MessageContent.Length != 0) {
        output.WriteRawTag(74);
        output.WriteString(MessageContent);
      }
      if (Reply != 0) {
        output.WriteRawTag(80);
        output.WriteEnum((int) Reply);
      }
      if (ReplyContent.Length != 0) {
        output.WriteRawTag(90);
        output.WriteString(ReplyContent);
      }
      groups_.WriteTo(output, _repeated_groups_codec);
      if (_unknownFields != null) {
        _unknownFields.WriteTo(output);
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public int CalculateSize() {
      int size = 0;
      if (MessageType != 0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) MessageType);
      }
      if (GroupActionType != 0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) GroupActionType);
      }
      if (AuthorizationType != 0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) AuthorizationType);
      }
      if (CommandType != 0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) CommandType);
      }
      if (Login.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(Login);
      }
      if (Password.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(Password);
      }
      if (GroupName.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(GroupName);
      }
      if (UserName.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(UserName);
      }
      if (MessageContent.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(MessageContent);
      }
      if (Reply != 0) {
        size += 1 + pb::CodedOutputStream.ComputeEnumSize((int) Reply);
      }
      if (ReplyContent.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(ReplyContent);
      }
      size += groups_.CalculateSize(_repeated_groups_codec);
      if (_unknownFields != null) {
        size += _unknownFields.CalculateSize();
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(ClientMessage other) {
      if (other == null) {
        return;
      }
      if (other.MessageType != 0) {
        MessageType = other.MessageType;
      }
      if (other.GroupActionType != 0) {
        GroupActionType = other.GroupActionType;
      }
      if (other.AuthorizationType != 0) {
        AuthorizationType = other.AuthorizationType;
      }
      if (other.CommandType != 0) {
        CommandType = other.CommandType;
      }
      if (other.Login.Length != 0) {
        Login = other.Login;
      }
      if (other.Password.Length != 0) {
        Password = other.Password;
      }
      if (other.GroupName.Length != 0) {
        GroupName = other.GroupName;
      }
      if (other.UserName.Length != 0) {
        UserName = other.UserName;
      }
      if (other.MessageContent.Length != 0) {
        MessageContent = other.MessageContent;
      }
      if (other.Reply != 0) {
        Reply = other.Reply;
      }
      if (other.ReplyContent.Length != 0) {
        ReplyContent = other.ReplyContent;
      }
      groups_.Add(other.groups_);
      _unknownFields = pb::UnknownFieldSet.MergeFrom(_unknownFields, other._unknownFields);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(pb::CodedInputStream input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            _unknownFields = pb::UnknownFieldSet.MergeFieldFrom(_unknownFields, input);
            break;
          case 8: {
            MessageType = (global::Message.ClientMessage.Types.messageTypes) input.ReadEnum();
            break;
          }
          case 16: {
            GroupActionType = (global::Message.ClientMessage.Types.groupActionTypes) input.ReadEnum();
            break;
          }
          case 24: {
            AuthorizationType = (global::Message.ClientMessage.Types.authorizationTypes) input.ReadEnum();
            break;
          }
          case 32: {
            CommandType = (global::Message.ClientMessage.Types.commandTypes) input.ReadEnum();
            break;
          }
          case 42: {
            Login = input.ReadString();
            break;
          }
          case 50: {
            Password = input.ReadString();
            break;
          }
          case 58: {
            GroupName = input.ReadString();
            break;
          }
          case 66: {
            UserName = input.ReadString();
            break;
          }
          case 74: {
            MessageContent = input.ReadString();
            break;
          }
          case 80: {
            Reply = (global::Message.ClientMessage.Types.replyStatus) input.ReadEnum();
            break;
          }
          case 90: {
            ReplyContent = input.ReadString();
            break;
          }
          case 98: {
            groups_.AddEntriesFrom(input, _repeated_groups_codec);
            break;
          }
        }
      }
    }

    #region Nested types
    /// <summary>Container for nested types declared in the ClientMessage message type.</summary>
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static partial class Types {
      public enum messageTypes {
        [pbr::OriginalName("AUTHORIZATION")] Authorization = 0,
        [pbr::OriginalName("COMMAND")] Command = 1,
        [pbr::OriginalName("GROUP")] Group = 2,
      }

      public enum groupActionTypes {
        [pbr::OriginalName("MESSAGE")] Message = 0,
        [pbr::OriginalName("CREATE")] Create = 1,
        [pbr::OriginalName("DELETE")] Delete = 2,
        [pbr::OriginalName("REQUEST")] Request = 3,
        [pbr::OriginalName("ACCEPT")] Accept = 4,
        [pbr::OriginalName("DECLINE")] Decline = 5,
        [pbr::OriginalName("LEAVE")] Leave = 6,
      }

      public enum authorizationTypes {
        [pbr::OriginalName("LOG_IN")] LogIn = 0,
        [pbr::OriginalName("REGISTER_LOGIN")] RegisterLogin = 1,
        [pbr::OriginalName("REGISTER_PASSWORD")] RegisterPassword = 2,
      }

      public enum commandTypes {
        [pbr::OriginalName("EXIT")] Exit = 0,
        [pbr::OriginalName("LOG_OUT")] LogOut = 1,
      }

      public enum replyStatus {
        [pbr::OriginalName("POSITIVE")] Positive = 0,
        [pbr::OriginalName("NEGATIVE")] Negative = 1,
      }

    }
    #endregion

  }

  #endregion

}

#endregion Designer generated code