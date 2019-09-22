/* SPDX-License-Identifier: GPL-3.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 2019 - 2020 Team 2896
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 3, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef KERNEL_HH
#define KERNEL_HH

#include <linux/types.h>
#include <thread>
#include <chrono>
#include <optional>

namespace team2896 {

    /**
     * @brief : (Safely) allocates memory from the heap.
     * @param : <_Ty> The data type's bytes to be allocated.
     * @param : <_Sz> The amount of _Ty types to be allocated.
     * @watch : Not marked with noexcept(true) to allow termination. */
    template <typename _Ty, const size_t _Sz>
    __attribute__ ((alwaysinline)) inline auto smalloc() -> decltype((void*)0)
    {
        void* flag = static_cast<void*>(malloc(sizeof(_Ty) * _Sz));
        return (flag != nullptr ? flag : nullptr);
    }

    /**
     * @brief : (Safely) frees memory from the heap.
     * @param : <MEMORY> The pointer to the allocated memory, from smalloc().
     * @watch : Not marked with noexcept(true) to allow termination. */
    __attribute__ ((alwaysinline)) inline std::optional<__u8> sfree(void* memory)
    {
        if (memory) {
            free(memory);
            return 0;
        } else {
            return {};
        }
    }

    /**
     * @brief : Returns the kernel's current time.
     * @watch : Marked with noexcept(true) to prevent termination. */
    __attribute__ ((alwaysinline)) inline const __kernel_clock_t now() noexcept(true)
    {
        using namespace std::chrono::_V2;
        auto time = high_resolution_clock::to_time_t(high_resolution_clock::now());
        return (time ? time : NULL);
    } 

    /**
     * @brief : Pauses the program's execution for TIME seconds.
     * @param : <TIME> The amount of seconds for the program to halt.
     * @watch : Marked with noexcept(true) to prevent termination. */
    __attribute__ ((noreturn)) inline void sleep(const __u8 time) noexcept(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(time));
    }

} // namespace team2896

#endif // KERNEL_HH
