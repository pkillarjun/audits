Bounty:
	@echo "bounty https://hackenproof.com/avalanche/avalanche-protocol"

all:
	@go test -fuzz=FuzzAliases -fuzztime=1800s github.com/ava-labs/avalanchego/genesis
	@go test -fuzz=FuzzBech32ToID -fuzztime=1800s github.com/ava-labs/avalanchego/vms/platformvm/api
	@go test -fuzz=FuzzBlock -fuzztime=1800s github.com/ava-labs/avalanchego/vms/proposervm/block
	@go test -fuzz=FuzzConfig -fuzztime=1800s github.com/ava-labs/avalanchego/genesis
	@go test -fuzz=FuzzEncodeDecode -fuzztime=1800s github.com/ava-labs/avalanchego/utils/cb58
	@go test -fuzz=FuzzEncodeDecode -fuzztime=1800s github.com/ava-labs/avalanchego/utils/formatting
	@go test -fuzz=FuzzGenesis -fuzztime=1800s github.com/ava-labs/avalanchego/genesis
	@go test -fuzz=FuzzGenesis -fuzztime=1800s github.com/ava-labs/avalanchego/vms/platformvm/genesis
	@go test -fuzz=FuzzIDs -fuzztime=1800s github.com/ava-labs/avalanchego/ids
	@go test -fuzz=FuzzInboundMessage -fuzztime=1800s github.com/ava-labs/avalanchego/message
	@go test -fuzz=FuzzKey -fuzztime=1800s github.com/ava-labs/avalanchego/tests
	@go test -fuzz=FuzzMessage -fuzztime=1800s github.com/ava-labs/avalanchego/vms/components/message
	@go test -fuzz=FuzzNetworkID -fuzztime=1800s github.com/ava-labs/avalanchego/utils/constants
	@go test -fuzz=FuzzNode -fuzztime=1800s github.com/ava-labs/avalanchego/x/merkledb
	@go test -fuzz=FuzzNodeIDb -fuzztime=1800s github.com/ava-labs/avalanchego/ids
	@go test -fuzz=FuzzNodeIDs -fuzztime=1800s github.com/ava-labs/avalanchego/ids
	@go test -fuzz=FuzzParse -fuzztime=1800s github.com/ava-labs/avalanchego/snow/engine/avalanche/vertex
	@go test -fuzz=FuzzParse -fuzztime=1800s github.com/ava-labs/avalanchego/version
	@go test -fuzz=FuzzParse -fuzztime=1800s github.com/ava-labs/avalanchego/vms/proposervm/summary
	@go test -fuzz=FuzzParseMessage -fuzztime=1800s github.com/ava-labs/avalanchego/vms/platformvm/warp
	@go test -fuzz=FuzzParseUM -fuzztime=1800s github.com/ava-labs/avalanchego/vms/platformvm/warp
	@go test -fuzz=FuzzUnmarshal -fuzztime=1800s github.com/ava-labs/avalanchego/message
	@go test -fuzz=FuzzUTXOID -fuzztime=1800s github.com/ava-labs/avalanchego/vms/components/avax
