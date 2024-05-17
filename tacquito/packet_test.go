/*
 Copyright (c) Facebook, Inc. and its affiliates.

 This source code is licensed under the MIT license found in the
 LICENSE file in the root directory of this source tree.
*/

package tacquito

import (
	"math/rand"
	"testing"
)

func FuzzAcctReply(f *testing.F) {

	v := NewAcctReply(
		SetAcctReplyStatus(AcctReplyStatusSuccess),
		SetAcctReplyServerMsg("i am a message from the server"),
		SetAcctReplyData("random data"),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AcctReply{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzAcctRequest(f *testing.F) {

	var f_ AcctRequestFlag
	f_.Set(AcctFlagStart)
	v := NewAcctRequest(
		SetAcctRequestFlag(f_),
		SetAcctRequestMethod(AuthenMethodTacacsPlus),
		SetAcctRequestPrivLvl(PrivLvlRoot),
		SetAcctRequestType(AuthenTypeASCII),
		SetAcctRequestService(AuthenServiceLogin),
		SetAcctRequestPort("4"),
		SetAcctRequestRemAddr("async"),
		SetAcctRequestArgs(Args{Arg("show"), Arg("system")}),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AcctRequest{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzAuthenContinue(f *testing.F) {

	v := NewAuthenContinue(
		SetAuthenContinueUserMessage("\nmore prompting"),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AuthenContinue{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzAuthenReply(f *testing.F) {

	v := NewAuthenReply(
		SetAuthenReplyStatus(AuthenStatusGetUser),
		SetAuthenReplyServerMsg("\nUser Access Verification\n\nUsername:"),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AuthenReply{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzAuthenStart(f *testing.F) {

	v := NewAuthenStart(
		SetAuthenStartAction(AuthenActionLogin),
		SetAuthenStartPrivLvl(PrivLvlRoot),
		SetAuthenStartType(AuthenTypeASCII),
		SetAuthenStartService(AuthenServiceLogin),
		SetAuthenStartPort("4"),
		SetAuthenStartRemAddr("async"),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AuthenStart{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzAuthorReply(f *testing.F) {

	v := NewAuthorReply(
		SetAuthorReplyStatus(AuthorStatusPassAdd),
		SetAuthorReplyArgs("show", "system"),
		SetAuthorReplyServerMsg("i am a message from the server"),
		SetAuthorReplyData("some data"),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AuthorReply{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzAuthorRequest(f *testing.F) {

	characters := []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")

	stringOfLength := func(n int) string {
		b := make([]rune, n)
		for i := range b {
			b[i] = characters[rand.Intn(len(characters))]
		}
		return string(b)
	}

	v := NewAuthorRequest(
		SetAuthorRequestMethod(AuthenMethodTacacsPlus),
		SetAuthorRequestPrivLvl(PrivLvlRoot),
		SetAuthorRequestType(AuthenTypeASCII),
		SetAuthorRequestService(AuthenServiceLogin),
		SetAuthorRequestPort("4"),
		SetAuthorRequestRemAddr("async"),
		SetAuthorRequestArgs(Args{Arg("show"), Arg("system"), Arg(stringOfLength(2)), Arg(stringOfLength(255))}),
	)
	buf, _ := v.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &AuthorRequest{}
		decoded.UnmarshalBinary(input)
	})
}

func FuzzPacket(f *testing.F) {

	var f_ HeaderFlag
	f_.Set(SingleConnect)
	h := NewHeader(
		SetHeaderVersion(Version{MajorVersion: MajorVersion, MinorVersion: MinorVersionOne}),
		SetHeaderType(Authenticate),
		SetHeaderSeqNo(1),
		SetHeaderFlag(f_),
		SetHeaderSessionID(12345),
		SetHeaderLen(int(MaxHeaderLength)),
	)
	p := NewPacket(SetPacketHeader(h), SetPacketBody(make([]byte, MaxBodyLength)))
	buf, _ := p.MarshalBinary()
	f.Add(buf)

	f.Fuzz(func(t *testing.T, input []byte) {

		decoded := &Packet{}
		decoded.UnmarshalBinary(input)
	})
}
