/* Copyright 2023 0x34d
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iomanip>

#include "vm/vm.h"
#include "vm/cp0.h"
#include "vm/dict.h"
#include "td/utils/tests.h"

std::string run_vm(td::Ref<vm::Cell> cell) {
    vm::init_op_cp0();
    vm::DictionaryBase::get_empty_dictionary();

    class Logger : public td::LogInterface {
        public:
            void append(td::CSlice slice) override {
                res.append(slice.data(), slice.size());
            }
        std::string res;
    };
    static Logger logger;
    logger.res = "";
    td::set_log_fatal_error_callback([](td::CSlice message) { td::default_log_interface->append(logger.res); });
    vm::VmLog log{&logger, td::LogOptions::plain()};
    log.log_options.level = 4;
    log.log_options.fix_newlines = true;
    log.log_mask |= vm::VmLog::DumpStack;

    auto total_data_cells_before = vm::DataCell::get_total_data_cells();
    SCOPE_EXIT {
        auto total_data_cells_after = vm::DataCell::get_total_data_cells();
        ASSERT_EQ(total_data_cells_before, total_data_cells_after);
    };

    vm::Stack stack;
    try {
        vm::GasLimits gas_limit(1000, 1000);

        vm::run_vm_code(vm::load_cell_slice_ref(cell), stack, 0 /*flags*/, nullptr /*data*/, std::move(log) /*VmLog*/,
                    nullptr, &gas_limit);
    } catch (...) {
        LOG(FATAL) << "catch unhandled exception";
    }
    return logger.res;  // must be a copy
}

td::Ref<vm::Cell> to_cell(const unsigned char *buff, int bits) {
    return vm::CellBuilder().store_bits(buff, bits, 0).finalize();
}

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 1;
    }

    try {
        run_vm(to_cell(Data, (int)Size));
    } catch(...) {
        // ignore
    }

    return 0;
}
