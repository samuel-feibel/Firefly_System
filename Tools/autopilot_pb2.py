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
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x0f\x61utopilot.proto\"\xe1\x01\n\tGPSStruct\x12\x0b\n\x03lat\x18\x01 \x01(\x02\x12\x0b\n\x03lon\x18\x02 \x01(\x02\x12\x0b\n\x03\x61lt\x18\x03 \x01(\x02\x12\x13\n\x0bgroundSpeed\x18\x04 \x01(\x02\x12\x0b\n\x03SIV\x18\x05 \x01(\x02\x12\x0f\n\x07heading\x18\x06 \x01(\x02\x12\x14\n\x0cposition_NED\x18\x07 \x03(\x02\x12\x0c\n\x04year\x18\x08 \x01(\x05\x12\r\n\x05month\x18\t \x01(\x05\x12\x0b\n\x03\x64\x61y\x18\n \x01(\x05\x12\x0c\n\x04hour\x18\x0b \x01(\x05\x12\x0e\n\x06minute\x18\x0c \x01(\x05\x12\x0e\n\x06second\x18\r \x01(\x05\x12\x0c\n\x04msec\x18\x0e \x01(\x05\"R\n\tIMUStruct\x12\x0b\n\x03\x61\x63\x63\x18\x01 \x03(\x02\x12\x0b\n\x03gyr\x18\x02 \x03(\x02\x12\x0b\n\x03mag\x18\x03 \x03(\x02\x12\x0e\n\x06rawMag\x18\x04 \x03(\x02\x12\x0e\n\x06rawGyr\x18\x05 \x03(\x02\"E\n\x0f\x42\x61rometerStruct\x12\x10\n\x08pressure\x18\x01 \x01(\x02\x12\x13\n\x0btemperature\x18\x02 \x01(\x02\x12\x0b\n\x03\x61lt\x18\x03 \x01(\x02\"|\n\x0cSensorStruct\x12\x17\n\x03GPS\x18\x01 \x01(\x0b\x32\n.GPSStruct\x12\x17\n\x03IMU\x18\x02 \x01(\x0b\x32\n.IMUStruct\x12\x1e\n\x04\x62\x61ro\x18\x03 \x01(\x0b\x32\x10.BarometerStruct\x12\x0f\n\x07z_input\x18\x04 \x03(\x02\x12\t\n\x01z\x18\x05 \x03(\x02\"/\n\x14StateEstimatorStruct\x12\x0c\n\x04xhat\x18\x01 \x03(\x02\x12\t\n\x01P\x18\x02 \x03(\x02\"/\n\x0cStatusStruct\x12\n\n\x02SD\x18\x01 \x01(\x08\x12\x13\n\x0bTransmitter\x18\x02 \x01(\x08\"/\n\nModeStruct\x12\x0f\n\x07\x61uxMode\x18\x01 \x01(\x05\x12\x10\n\x08\x61utoMode\x18\x02 \x01(\x05\"\xb1\x01\n\x08PlaneBuf\x12\x0c\n\x04\x64\x65lt\x18\x01 \x01(\x02\x12\x1e\n\x07sensors\x18\x02 \x01(\x0b\x32\r.SensorStruct\x12-\n\x0estateEstimator\x18\x03 \x01(\x0b\x32\x15.StateEstimatorStruct\x12\x1d\n\x06status\x18\x04 \x01(\x0b\x32\r.StatusStruct\x12\x19\n\x04mode\x18\x05 \x01(\x0b\x32\x0b.ModeStruct\x12\x0e\n\x06mcTime\x18\x06 \x01(\x02\x62\x06proto3'
)




_GPSSTRUCT = _descriptor.Descriptor(
  name='GPSStruct',
  full_name='GPSStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='lat', full_name='GPSStruct.lat', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='lon', full_name='GPSStruct.lon', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='alt', full_name='GPSStruct.alt', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='groundSpeed', full_name='GPSStruct.groundSpeed', index=3,
      number=4, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='SIV', full_name='GPSStruct.SIV', index=4,
      number=5, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='heading', full_name='GPSStruct.heading', index=5,
      number=6, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='position_NED', full_name='GPSStruct.position_NED', index=6,
      number=7, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='year', full_name='GPSStruct.year', index=7,
      number=8, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='month', full_name='GPSStruct.month', index=8,
      number=9, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='day', full_name='GPSStruct.day', index=9,
      number=10, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='hour', full_name='GPSStruct.hour', index=10,
      number=11, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='minute', full_name='GPSStruct.minute', index=11,
      number=12, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='second', full_name='GPSStruct.second', index=12,
      number=13, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='msec', full_name='GPSStruct.msec', index=13,
      number=14, type=5, cpp_type=1, label=1,
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=20,
  serialized_end=245,
)


_IMUSTRUCT = _descriptor.Descriptor(
  name='IMUStruct',
  full_name='IMUStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='acc', full_name='IMUStruct.acc', index=0,
      number=1, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='gyr', full_name='IMUStruct.gyr', index=1,
      number=2, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mag', full_name='IMUStruct.mag', index=2,
      number=3, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='rawMag', full_name='IMUStruct.rawMag', index=3,
      number=4, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='rawGyr', full_name='IMUStruct.rawGyr', index=4,
      number=5, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=247,
  serialized_end=329,
)


_BAROMETERSTRUCT = _descriptor.Descriptor(
  name='BarometerStruct',
  full_name='BarometerStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='pressure', full_name='BarometerStruct.pressure', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='temperature', full_name='BarometerStruct.temperature', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='alt', full_name='BarometerStruct.alt', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=331,
  serialized_end=400,
)


_SENSORSTRUCT = _descriptor.Descriptor(
  name='SensorStruct',
  full_name='SensorStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='GPS', full_name='SensorStruct.GPS', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='IMU', full_name='SensorStruct.IMU', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='baro', full_name='SensorStruct.baro', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='z_input', full_name='SensorStruct.z_input', index=3,
      number=4, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='z', full_name='SensorStruct.z', index=4,
      number=5, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=402,
  serialized_end=526,
)


_STATEESTIMATORSTRUCT = _descriptor.Descriptor(
  name='StateEstimatorStruct',
  full_name='StateEstimatorStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='xhat', full_name='StateEstimatorStruct.xhat', index=0,
      number=1, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='P', full_name='StateEstimatorStruct.P', index=1,
      number=2, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=528,
  serialized_end=575,
)


_STATUSSTRUCT = _descriptor.Descriptor(
  name='StatusStruct',
  full_name='StatusStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='SD', full_name='StatusStruct.SD', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='Transmitter', full_name='StatusStruct.Transmitter', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=577,
  serialized_end=624,
)


_MODESTRUCT = _descriptor.Descriptor(
  name='ModeStruct',
  full_name='ModeStruct',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='auxMode', full_name='ModeStruct.auxMode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='autoMode', full_name='ModeStruct.autoMode', index=1,
      number=2, type=5, cpp_type=1, label=1,
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=626,
  serialized_end=673,
)


_PLANEBUF = _descriptor.Descriptor(
  name='PlaneBuf',
  full_name='PlaneBuf',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='delt', full_name='PlaneBuf.delt', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='sensors', full_name='PlaneBuf.sensors', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='stateEstimator', full_name='PlaneBuf.stateEstimator', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='status', full_name='PlaneBuf.status', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mode', full_name='PlaneBuf.mode', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mcTime', full_name='PlaneBuf.mcTime', index=5,
      number=6, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
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
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=676,
  serialized_end=853,
)

_SENSORSTRUCT.fields_by_name['GPS'].message_type = _GPSSTRUCT
_SENSORSTRUCT.fields_by_name['IMU'].message_type = _IMUSTRUCT
_SENSORSTRUCT.fields_by_name['baro'].message_type = _BAROMETERSTRUCT
_PLANEBUF.fields_by_name['sensors'].message_type = _SENSORSTRUCT
_PLANEBUF.fields_by_name['stateEstimator'].message_type = _STATEESTIMATORSTRUCT
_PLANEBUF.fields_by_name['status'].message_type = _STATUSSTRUCT
_PLANEBUF.fields_by_name['mode'].message_type = _MODESTRUCT
DESCRIPTOR.message_types_by_name['GPSStruct'] = _GPSSTRUCT
DESCRIPTOR.message_types_by_name['IMUStruct'] = _IMUSTRUCT
DESCRIPTOR.message_types_by_name['BarometerStruct'] = _BAROMETERSTRUCT
DESCRIPTOR.message_types_by_name['SensorStruct'] = _SENSORSTRUCT
DESCRIPTOR.message_types_by_name['StateEstimatorStruct'] = _STATEESTIMATORSTRUCT
DESCRIPTOR.message_types_by_name['StatusStruct'] = _STATUSSTRUCT
DESCRIPTOR.message_types_by_name['ModeStruct'] = _MODESTRUCT
DESCRIPTOR.message_types_by_name['PlaneBuf'] = _PLANEBUF
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

GPSStruct = _reflection.GeneratedProtocolMessageType('GPSStruct', (_message.Message,), {
  'DESCRIPTOR' : _GPSSTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:GPSStruct)
  })
_sym_db.RegisterMessage(GPSStruct)

IMUStruct = _reflection.GeneratedProtocolMessageType('IMUStruct', (_message.Message,), {
  'DESCRIPTOR' : _IMUSTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:IMUStruct)
  })
_sym_db.RegisterMessage(IMUStruct)

BarometerStruct = _reflection.GeneratedProtocolMessageType('BarometerStruct', (_message.Message,), {
  'DESCRIPTOR' : _BAROMETERSTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:BarometerStruct)
  })
_sym_db.RegisterMessage(BarometerStruct)

SensorStruct = _reflection.GeneratedProtocolMessageType('SensorStruct', (_message.Message,), {
  'DESCRIPTOR' : _SENSORSTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:SensorStruct)
  })
_sym_db.RegisterMessage(SensorStruct)

StateEstimatorStruct = _reflection.GeneratedProtocolMessageType('StateEstimatorStruct', (_message.Message,), {
  'DESCRIPTOR' : _STATEESTIMATORSTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:StateEstimatorStruct)
  })
_sym_db.RegisterMessage(StateEstimatorStruct)

StatusStruct = _reflection.GeneratedProtocolMessageType('StatusStruct', (_message.Message,), {
  'DESCRIPTOR' : _STATUSSTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:StatusStruct)
  })
_sym_db.RegisterMessage(StatusStruct)

ModeStruct = _reflection.GeneratedProtocolMessageType('ModeStruct', (_message.Message,), {
  'DESCRIPTOR' : _MODESTRUCT,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:ModeStruct)
  })
_sym_db.RegisterMessage(ModeStruct)

PlaneBuf = _reflection.GeneratedProtocolMessageType('PlaneBuf', (_message.Message,), {
  'DESCRIPTOR' : _PLANEBUF,
  '__module__' : 'autopilot_pb2'
  # @@protoc_insertion_point(class_scope:PlaneBuf)
  })
_sym_db.RegisterMessage(PlaneBuf)


# @@protoc_insertion_point(module_scope)
