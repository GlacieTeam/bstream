# Copyright © 2025 GlacieTeam.All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# SPDX-License-Identifier: MPL-2.0

from typing import overload, Union

class ReadOnlyBinaryStream:
    def __eq__(self, other: ReadOnlyBinaryStream) -> bool: ...
    def __init__(
        self,
        buffer: Union[bytes, bytearray],
        copy_buffer: bool = False,
        big_endian: bool = False,
    ) -> None:
        """Construct from a buffer (bytes or bytearray)
        Args:
            buffer: Binary data as bytes or bytearray
            copy_buffer: If True, copy the data (always True for bytes)
            big_endian: Endianness for reading numbers"""

    def __len__(self) -> int: ...
    def __repr__(self) -> str: ...
    def copy_data(self) -> bytes:
        """Get a copy of the entire buffer"""

    def get_bool(self) -> bool:
        """Read boolean"""

    def get_byte(self) -> int:
        """Read unsigned char"""

    def get_bytes(self) -> bytes:
        """Read a bytes"""

    def get_short_bytes(self) -> bytes:
        """Read a short bytes"""

    def get_long_bytes(self) -> bytes:
        """Read a long bytes"""

    def get_double(self) -> float:
        """Read double"""

    def get_float(self) -> float:
        """Read float"""

    def get_left_buffer(self) -> bytes:
        """Get remaining data as bytes"""

    def get_normalized_float(self) -> float:
        """Read normalized float"""

    def get_position(self) -> int: ...
    def get_raw_bytes(self, length: int) -> bytes:
        """Read raw bytes of specified length"""

    def get_signed_big_endian_int(self) -> int:
        """Read big-endian signed int"""

    def get_signed_int(self) -> int:
        """Read signed int"""

    def get_signed_int64(self) -> int:
        """Read signed int64"""

    def get_signed_short(self) -> int:
        """Read signed short"""

    def get_string(self) -> str:
        """Read a string"""

    def get_short_string(self) -> str:
        """Read a short string"""

    def get_long_string(self) -> str:
        """Read a long string"""

    def get_unsigned_char(self) -> int:
        """Read unsigned char"""

    def get_unsigned_int(self) -> int:
        """Read unsigned int"""

    def get_unsigned_int24(self) -> int:
        """Read 24-bit unsigned int"""

    def get_unsigned_int64(self) -> int:
        """Read unsigned int64"""

    def get_unsigned_short(self) -> int:
        """Read unsigned short"""

    def get_unsigned_varint(self) -> int:
        """Read unsigned varint"""

    def get_unsigned_varint64(self) -> int:
        """Read unsigned varint64"""

    def get_varint(self) -> int:
        """Read varint"""

    def get_varint64(self) -> int:
        """Read varint64"""

    def has_data_left(self) -> bool: ...
    def has_overflowed(self) -> bool: ...
    def ignore_bytes(self, length: int) -> None: ...
    def reset_position(self) -> None: ...
    def set_position(self, position: int) -> None: ...
    def size(self) -> int: ...

class BinaryStream(ReadOnlyBinaryStream):
    @overload
    def __init__(self, big_endian: bool = False) -> None:
        """Create a new empty BinaryStream
        Args:
            big_endian: Endianness for writing numbers"""

    @overload
    def __init__(
        self, buffer: Union[bytes, bytearray], big_endian: bool = False
    ) -> None:
        """Construct from a buffer (bytes or bytearray)
        Args:
            buffer: Binary data as bytes or bytearray
            copy_buffer: If True, copy the data
            big_endian: Endianness for writing numbers"""

    def __repr__(self) -> str: ...
    def copy_buffer(self) -> bytes:
        """Get copy of internal data buffer"""

    def data(self) -> bytes:
        """Get copy of internal data buffer"""

    def get_and_release_data(self) -> bytes:
        """Get and release internal data buffer"""

    def reserve(self, size: int) -> None:
        """Reserve internal buffer size"""

    def reset(self) -> None:
        """Reset stream to initial state"""

    def write_bool(self, value: bool) -> None:
        """Write bool"""

    def write_byte(self, value: int) -> None:
        """Write unsigned char"""

    def write_bytes(self, value: Union[bytes, bytearray]) -> None:
        """Write a bytes"""

    def write_short_bytes(self, value: Union[bytes, bytearray]) -> None:
        """Write a short bytes"""

    def write_long_bytes(self, value: Union[bytes, bytearray]) -> None:
        """Write a long bytes"""

    def write_double(self, value: float) -> None:
        """Write double"""

    def write_float(self, value: float) -> None:
        """Write float"""

    def write_normalized_float(self, value: float) -> None:
        """Write normalized float"""

    @overload
    def write_raw_bytes(self, raw_buffer: Union[bytes, bytearray]) -> None:
        """Write raw bytes"""

    @overload
    def write_raw_bytes(self, raw_buffer: Union[bytes, bytearray], size: int) -> None:
        """Write raw bytes with specified length"""

    def write_signed_big_endian_int(self, value: int) -> None:
        """write signed big endian int"""

    def write_signed_int(self, value: int) -> None:
        """Write signed int"""

    def write_signed_int64(self, value: int) -> None:
        """Write signed int64"""

    def write_signed_short(self, value: int) -> None:
        """Write signed short"""

    def write_stream(self, stream: ReadOnlyBinaryStream) -> None:
        """Write content from another stream"""

    def write_string(self, value: str) -> None:
        """Write a string"""

    def write_short_string(self, value: str) -> None:
        """Write a short string"""

    def write_long_string(self, value: str) -> None:
        """Write a long string"""

    def write_unsigned_char(self, value: int) -> None:
        """Write unsigned char"""

    def write_unsigned_int(self, value: int) -> None:
        """Write unsigned int"""

    def write_unsigned_int24(self, value: int) -> None:
        """write unsigned int24"""

    def write_unsigned_int64(self, value: int) -> None:
        """Write unsigned int64"""

    def write_unsigned_short(self, value: int) -> None:
        """Write unsigned short"""

    def write_unsigned_varint(self, value: int) -> None:
        """Write unsigned varint"""

    def write_unsigned_varint64(self, value: int) -> None:
        """Write unsigned varint64"""

    def write_varint(self, value: int) -> None:
        """Write varint"""

    def write_varint64(self, value: int) -> None:
        """Write varint64"""
