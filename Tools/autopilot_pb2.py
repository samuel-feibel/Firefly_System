# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: autopilot.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='autopilot.proto',
  package='',
  syntax='proto2',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x0f\x61utopilot.proto\"\x18\n\x07\x45xample\x12\r\n\x05value\x18\x01 \x02(\x05'
)




_EXAMPLE = _descriptor.Descriptor(
  name='Example',
  full_name='Example',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='value', full_name='Example.value', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=19,
  serialized_end=43,
)

DESCRIPTOR.message_types_by_name['Example'] = _EXAMPLE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Example = _reflection.GeneratedProtocolMessageType('Example', (_message.Message,), {
  'DESCRIPTOR' : _EXAMPLE,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:Example)
  })
_sym_db.RegisterMessage(Example)


# @@protoc_insertion_point(module_scope)
