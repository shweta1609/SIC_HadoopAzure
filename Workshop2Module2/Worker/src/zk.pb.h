// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: zk.proto

#ifndef PROTOBUF_INCLUDED_zk_2eproto
#define PROTOBUF_INCLUDED_zk_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_zk_2eproto 

namespace protobuf_zk_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_zk_2eproto
namespace masterworker {
class AliveRequest;
class AliveRequestDefaultTypeInternal;
extern AliveRequestDefaultTypeInternal _AliveRequest_default_instance_;
class AliveResponse;
class AliveResponseDefaultTypeInternal;
extern AliveResponseDefaultTypeInternal _AliveResponse_default_instance_;
}  // namespace masterworker
namespace google {
namespace protobuf {
template<> ::masterworker::AliveRequest* Arena::CreateMaybeMessage<::masterworker::AliveRequest>(Arena*);
template<> ::masterworker::AliveResponse* Arena::CreateMaybeMessage<::masterworker::AliveResponse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace masterworker {

// ===================================================================

class AliveRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterworker.AliveRequest) */ {
 public:
  AliveRequest();
  virtual ~AliveRequest();

  AliveRequest(const AliveRequest& from);

  inline AliveRequest& operator=(const AliveRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AliveRequest(AliveRequest&& from) noexcept
    : AliveRequest() {
    *this = ::std::move(from);
  }

  inline AliveRequest& operator=(AliveRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const AliveRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AliveRequest* internal_default_instance() {
    return reinterpret_cast<const AliveRequest*>(
               &_AliveRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(AliveRequest* other);
  friend void swap(AliveRequest& a, AliveRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AliveRequest* New() const final {
    return CreateMaybeMessage<AliveRequest>(NULL);
  }

  AliveRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<AliveRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const AliveRequest& from);
  void MergeFrom(const AliveRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AliveRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string aliveQuery = 1;
  void clear_alivequery();
  static const int kAliveQueryFieldNumber = 1;
  const ::std::string& alivequery() const;
  void set_alivequery(const ::std::string& value);
  #if LANG_CXX11
  void set_alivequery(::std::string&& value);
  #endif
  void set_alivequery(const char* value);
  void set_alivequery(const char* value, size_t size);
  ::std::string* mutable_alivequery();
  ::std::string* release_alivequery();
  void set_allocated_alivequery(::std::string* alivequery);

  // @@protoc_insertion_point(class_scope:masterworker.AliveRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr alivequery_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_zk_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class AliveResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterworker.AliveResponse) */ {
 public:
  AliveResponse();
  virtual ~AliveResponse();

  AliveResponse(const AliveResponse& from);

  inline AliveResponse& operator=(const AliveResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AliveResponse(AliveResponse&& from) noexcept
    : AliveResponse() {
    *this = ::std::move(from);
  }

  inline AliveResponse& operator=(AliveResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const AliveResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AliveResponse* internal_default_instance() {
    return reinterpret_cast<const AliveResponse*>(
               &_AliveResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(AliveResponse* other);
  friend void swap(AliveResponse& a, AliveResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AliveResponse* New() const final {
    return CreateMaybeMessage<AliveResponse>(NULL);
  }

  AliveResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<AliveResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const AliveResponse& from);
  void MergeFrom(const AliveResponse& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AliveResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string reply = 1;
  void clear_reply();
  static const int kReplyFieldNumber = 1;
  const ::std::string& reply() const;
  void set_reply(const ::std::string& value);
  #if LANG_CXX11
  void set_reply(::std::string&& value);
  #endif
  void set_reply(const char* value);
  void set_reply(const char* value, size_t size);
  ::std::string* mutable_reply();
  ::std::string* release_reply();
  void set_allocated_reply(::std::string* reply);

  // @@protoc_insertion_point(class_scope:masterworker.AliveResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr reply_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_zk_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// AliveRequest

// string aliveQuery = 1;
inline void AliveRequest::clear_alivequery() {
  alivequery_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& AliveRequest::alivequery() const {
  // @@protoc_insertion_point(field_get:masterworker.AliveRequest.aliveQuery)
  return alivequery_.GetNoArena();
}
inline void AliveRequest::set_alivequery(const ::std::string& value) {
  
  alivequery_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:masterworker.AliveRequest.aliveQuery)
}
#if LANG_CXX11
inline void AliveRequest::set_alivequery(::std::string&& value) {
  
  alivequery_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:masterworker.AliveRequest.aliveQuery)
}
#endif
inline void AliveRequest::set_alivequery(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  alivequery_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:masterworker.AliveRequest.aliveQuery)
}
inline void AliveRequest::set_alivequery(const char* value, size_t size) {
  
  alivequery_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:masterworker.AliveRequest.aliveQuery)
}
inline ::std::string* AliveRequest::mutable_alivequery() {
  
  // @@protoc_insertion_point(field_mutable:masterworker.AliveRequest.aliveQuery)
  return alivequery_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* AliveRequest::release_alivequery() {
  // @@protoc_insertion_point(field_release:masterworker.AliveRequest.aliveQuery)
  
  return alivequery_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AliveRequest::set_allocated_alivequery(::std::string* alivequery) {
  if (alivequery != NULL) {
    
  } else {
    
  }
  alivequery_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), alivequery);
  // @@protoc_insertion_point(field_set_allocated:masterworker.AliveRequest.aliveQuery)
}

// -------------------------------------------------------------------

// AliveResponse

// string reply = 1;
inline void AliveResponse::clear_reply() {
  reply_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& AliveResponse::reply() const {
  // @@protoc_insertion_point(field_get:masterworker.AliveResponse.reply)
  return reply_.GetNoArena();
}
inline void AliveResponse::set_reply(const ::std::string& value) {
  
  reply_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:masterworker.AliveResponse.reply)
}
#if LANG_CXX11
inline void AliveResponse::set_reply(::std::string&& value) {
  
  reply_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:masterworker.AliveResponse.reply)
}
#endif
inline void AliveResponse::set_reply(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  reply_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:masterworker.AliveResponse.reply)
}
inline void AliveResponse::set_reply(const char* value, size_t size) {
  
  reply_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:masterworker.AliveResponse.reply)
}
inline ::std::string* AliveResponse::mutable_reply() {
  
  // @@protoc_insertion_point(field_mutable:masterworker.AliveResponse.reply)
  return reply_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* AliveResponse::release_reply() {
  // @@protoc_insertion_point(field_release:masterworker.AliveResponse.reply)
  
  return reply_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AliveResponse::set_allocated_reply(::std::string* reply) {
  if (reply != NULL) {
    
  } else {
    
  }
  reply_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), reply);
  // @@protoc_insertion_point(field_set_allocated:masterworker.AliveResponse.reply)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace masterworker

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_zk_2eproto
