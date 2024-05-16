// Copyright (C) 2019-2023, Ava Labs, Inc. All rights reserved.
// See the file LICENSE for licensing terms.

package genesis

import (
	"testing"
)

func FuzzGenesis(f *testing.F) {

	f.Fuzz(func(t *testing.T, orig []byte) {
		Parse(orig)
		ParseState(orig)
	})
}
