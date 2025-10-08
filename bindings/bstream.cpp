// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include <bstream.hpp>
#include <format>
#include <pybind11/buffer_info.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

inline py::bytes to_pybytes(std::string_view sv) { return py::bytes(sv.data(), sv.size()); }

inline py::bytes to_pybytes(std::string const& s) { return py::bytes(s); }

PYBIND11_MODULE(_bstream, m) {
    m.doc() = "Python bindings for bstream library";

    py::class_<bstream::ReadOnlyBinaryStream>(m, "ReadOnlyBinaryStream")
        .def(
            py::init([](py::buffer buf, bool copy_buffer = false, bool big_endian = false) {
                py::buffer_info info = buf.request();
                const char*     data = static_cast<const char*>(info.ptr);
                size_t          size = info.size;
                if (!copy_buffer && PyBytes_Check(buf.ptr())) { copy_buffer = true; }
                return std::make_unique<bstream::ReadOnlyBinaryStream>(data, size, copy_buffer, big_endian);
            }),
            py::arg("buffer"),
            py::arg("copy_buffer") = false,
            py::arg("big_endian")  = false,
            R"doc(
Construct from a buffer (bytes or bytearray)
        
Args:
    buffer: Binary data as bytes or bytearray
    copy_buffer: If True, copy the data (always True for bytes)
    big_endian: Endianness for reading numbers
)doc"
        )
        .def("size", &bstream::ReadOnlyBinaryStream::size)
        .def("get_position", &bstream::ReadOnlyBinaryStream::getPosition)
        .def("set_position", &bstream::ReadOnlyBinaryStream::setPosition, py::arg("position"))
        .def("reset_position", &bstream::ReadOnlyBinaryStream::resetPosition)
        .def("ignore_bytes", &bstream::ReadOnlyBinaryStream::ignoreBytes, py::arg("length"))
        .def("has_overflowed", &bstream::ReadOnlyBinaryStream::isOverflowed)
        .def("has_data_left", &bstream::ReadOnlyBinaryStream::hasDataLeft)
        .def(
            "get_left_buffer",
            [](bstream::ReadOnlyBinaryStream& self) -> py::bytes { return to_pybytes(self.getLeftBuffer()); },
            "Get remaining data as bytes"
        )
        .def(
            "copy_data",
            [](bstream::ReadOnlyBinaryStream& self) -> py::bytes { return to_pybytes(self.copyData()); },
            "Get a copy of the entire buffer"
        )

        .def("get_byte", &bstream::ReadOnlyBinaryStream::getUnsignedChar, "Read unsigned char")
        .def("get_unsigned_char", &bstream::ReadOnlyBinaryStream::getUnsignedChar, "Read unsigned char")
        .def("get_unsigned_short", &bstream::ReadOnlyBinaryStream::getUnsignedShort, "Read unsigned short")
        .def("get_unsigned_int", &bstream::ReadOnlyBinaryStream::getUnsignedInt, "Read unsigned int")
        .def("get_unsigned_int64", &bstream::ReadOnlyBinaryStream::getUnsignedInt64, "Read unsigned int64")
        .def("get_bool", &bstream::ReadOnlyBinaryStream::getBool, "Read boolean")
        .def("get_double", &bstream::ReadOnlyBinaryStream::getDouble, "Read double")
        .def("get_float", &bstream::ReadOnlyBinaryStream::getFloat, "Read float")
        .def("get_signed_int", &bstream::ReadOnlyBinaryStream::getSignedInt, "Read signed int")
        .def("get_signed_int64", &bstream::ReadOnlyBinaryStream::getSignedInt64, "Read signed int64")
        .def("get_signed_short", &bstream::ReadOnlyBinaryStream::getSignedShort, "Read signed short")
        .def("get_unsigned_varint", &bstream::ReadOnlyBinaryStream::getUnsignedVarInt, "Read unsigned varint")
        .def("get_unsigned_varint64", &bstream::ReadOnlyBinaryStream::getUnsignedVarInt64, "Read unsigned varint64")
        .def("get_varint", &bstream::ReadOnlyBinaryStream::getVarInt, "Read varint")
        .def("get_varint64", &bstream::ReadOnlyBinaryStream::getVarInt64, "Read varint64")
        .def("get_normalized_float", &bstream::ReadOnlyBinaryStream::getNormalizedFloat, "Read normalized float")
        .def(
            "get_signed_big_endian_int",
            &bstream::ReadOnlyBinaryStream::getSignedBigEndianInt,
            "Read big-endian signed int"
        )
        .def("get_unsigned_int24", &bstream::ReadOnlyBinaryStream::getUnsignedInt24, "Read 24-bit unsigned int")
        .def(
            "get_bytes",
            [](bstream::ReadOnlyBinaryStream& self) -> py::bytes { return to_pybytes(self.getString()); },
            "Read a bytes"
        )
        .def(
            "get_string",
            [](bstream::ReadOnlyBinaryStream& self) -> std::string { return self.getString(); },
            "Read a string"
        )
        .def(
            "get_short_bytes",
            [](bstream::ReadOnlyBinaryStream& self) -> py::bytes { return to_pybytes(self.getShortString()); },
            "Read a bytes"
        )
        .def(
            "get_short_string",
            [](bstream::ReadOnlyBinaryStream& self) -> std::string { return self.getShortString(); },
            "Read a string"
        )
        .def(
            "get_long_bytes",
            [](bstream::ReadOnlyBinaryStream& self) -> py::bytes { return to_pybytes(self.getLongString()); },
            "Read a bytes"
        )
        .def(
            "get_long_string",
            [](bstream::ReadOnlyBinaryStream& self) -> std::string { return self.getLongString(); },
            "Read a string"
        )
        .def(
            "get_raw_bytes",
            [](bstream::ReadOnlyBinaryStream& self, size_t length) -> py::bytes {
                return to_pybytes(self.getRawBytes(length));
            },
            py::arg("length"),
            "Read raw bytes of specified length"
        )

        .def("__eq__", &bstream::ReadOnlyBinaryStream::operator==, py::arg("other"))
        .def("__len__", &bstream::ReadOnlyBinaryStream::size)
        .def("__repr__", [](bstream::ReadOnlyBinaryStream const& self) {
            return std::format("<ReadOnlyBinaryStream size={0}, position={1}", self.size(), self.getPosition());
        });


    py::class_<bstream::BinaryStream, bstream::ReadOnlyBinaryStream>(m, "BinaryStream")
        .def(
            py::init<bool>(),
            py::arg("big_endian") = false,
            R"doc(
            Create a new empty BinaryStream
             
            Args:
                big_endian: Endianness for writing numbers
            )doc"
        )
        .def(
            py::init([](py::buffer buf, bool big_endian) {
                py::buffer_info info   = buf.request();
                const char*     data   = static_cast<const char*>(info.ptr);
                size_t          size   = static_cast<size_t>(info.size);
                std::string     buffer = std::string(data, size);
                return std::make_unique<bstream::BinaryStream>(buffer, true, big_endian);
            }),
            py::arg("buffer"),
            py::arg("big_endian") = false,
            R"doc(
            Construct from a buffer (bytes or bytearray)
    
            Args:
                buffer: Binary data as bytes or bytearray
                copy_buffer: If True, copy the data
                big_endian: Endianness for writing numbers
            )doc"
        )
        .def("reserve", &bstream::BinaryStream::reserve, py::arg("size"), "Reserve internal buffer size")
        .def("reset", &bstream::BinaryStream::reset, "Reset stream to initial state")
        .def(
            "data",
            [](bstream::BinaryStream& self) -> py::bytes { return to_pybytes(self.data()); },
            "Get copy of internal data buffer"
        )
        .def(
            "copy_buffer",
            [](bstream::BinaryStream& self) -> py::bytes { return to_pybytes(self.copyBuffer()); },
            "Get copy of internal data buffer"
        )
        .def(
            "get_and_release_data",
            [](bstream::BinaryStream& self) -> py::bytes { return to_pybytes(self.getAndReleaseData()); },
            "Get and release internal data buffer"
        )

        .def("write_byte", &bstream::BinaryStream::writeUnsignedChar, py::arg("value"), "Write unsigned char")
        .def("write_unsigned_char", &bstream::BinaryStream::writeUnsignedChar, py::arg("value"), "Write unsigned char")
        .def(
            "write_unsigned_short",
            &bstream::BinaryStream::writeUnsignedShort,
            py::arg("value"),
            "Write unsigned short"
        )
        .def("write_unsigned_int", &bstream::BinaryStream::writeUnsignedInt, py::arg("value"), "Write unsigned int")
        .def(
            "write_unsigned_int64",
            &bstream::BinaryStream::writeUnsignedInt64,
            py::arg("value"),
            "Write unsigned int64"
        )
        .def("write_bool", &bstream::BinaryStream::writeBool, py::arg("value"), "Write bool")
        .def("write_double", &bstream::BinaryStream::writeDouble, py::arg("value"), "Write double")
        .def("write_float", &bstream::BinaryStream::writeFloat, py::arg("value"), "Write float")
        .def("write_signed_int", &bstream::BinaryStream::writeSignedInt, py::arg("value"), "Write signed int")
        .def("write_signed_int64", &bstream::BinaryStream::writeSignedInt64, py::arg("value"), "Write signed int64")
        .def("write_signed_short", &bstream::BinaryStream::writeSignedShort, py::arg("value"), "Write signed short")
        .def(
            "write_unsigned_varint",
            &bstream::BinaryStream::writeUnsignedVarInt,
            py::arg("value"),
            "Write unsigned varint"
        )
        .def(
            "write_unsigned_varint64",
            &bstream::BinaryStream::writeUnsignedVarInt64,
            py::arg("value"),
            "Write unsigned varint64"
        )
        .def("write_varint", &bstream::BinaryStream::writeVarInt, py::arg("value"), "Write varint")
        .def("write_varint64", &bstream::BinaryStream::writeVarInt64, py::arg("value"), "Write varint64")
        .def(
            "write_normalized_float",
            &bstream::BinaryStream::writeNormalizedFloat,
            py::arg("value"),
            "Write normalized float"
        )
        .def(
            "write_signed_big_endian_int",
            &bstream::BinaryStream::writeSignedBigEndianInt,
            py::arg("value"),
            "write signed big endian int"
        )
        .def(
            "write_unsigned_int24",
            &bstream::BinaryStream::writeUnsignedInt24,
            py::arg("value"),
            "write unsigned int24"
        )
        .def(
            "write_short_bytes",
            [](bstream::BinaryStream& self, py::buffer value) {
                py::buffer_info info = value.request();
                self.writeShortString(std::string_view(static_cast<const char*>(info.ptr), info.size));
            },
            py::arg("value"),
            "Write a short bytes"
        )
        .def(
            "write_short_string",
            &bstream::BinaryStream::writeShortString,
            py::arg("value"),
            "Write a short text string"
        )
        .def(
            "write_long_bytes",
            [](bstream::BinaryStream& self, py::buffer value) {
                py::buffer_info info = value.request();
                self.writeLongString(std::string_view(static_cast<const char*>(info.ptr), info.size));
            },
            py::arg("value"),
            "Write a long bytes"
        )
        .def("write_long_string", &bstream::BinaryStream::writeLongString, py::arg("value"), "Write a long string")
        .def(
            "write_bytes",
            [](bstream::BinaryStream& self, py::buffer value) {
                py::buffer_info info = value.request();
                self.writeString(std::string_view(static_cast<const char*>(info.ptr), info.size));
            },
            py::arg("value"),
            "Write a bytes"
        )
        .def("write_string", &bstream::BinaryStream::writeString, py::arg("value"), "Write a string")
        .def(
            "write_raw_bytes",
            [](bstream::BinaryStream& self, py::buffer raw_buffer) {
                py::buffer_info info = raw_buffer.request();
                self.writeRawBytes(std::string_view(static_cast<const char*>(info.ptr), info.size));
            },
            py::arg("raw_buffer"),
            "Write raw bytes"
        )
        .def(
            "write_raw_bytes",
            [](bstream::BinaryStream& self, py::buffer raw_buffer, size_t size) {
                py::buffer_info info = raw_buffer.request();
                if (info.size < static_cast<int64_t>(size)) {
                    throw std::runtime_error("Buffer size is smaller than requested length");
                }
                self.writeRawBytes(std::string_view(static_cast<const char*>(info.ptr), size));
            },
            py::arg("raw_buffer"),
            py::arg("size"),
            "Write raw bytes with specified length"
        )

        .def(
            "write_stream",
            [](bstream::BinaryStream& self, bstream::ReadOnlyBinaryStream& stream) { self.writeStream(stream); },
            py::arg("stream"),
            "Write content from another stream"
        )

        .def("__repr__", [](const bstream::BinaryStream& self) {
            return std::format("<BinaryStream size={0}, position={1}>", self.size(), self.getPosition());
        });
}
