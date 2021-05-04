#pragma once
#include <cstdint>
#include <pulse/pulseaudio.h>

namespace Soundux
{
    namespace PulseApi
    {
        // TODO(curve): Acquire functions with dlopen at runtime

        inline pa_mainloop *(*pa_mainloop_new)();
        inline int (*pa_mainloop_iterate)(pa_mainloop *, int, int *);
        inline pa_mainloop_api *(*pa_mainloop_get_api)(pa_mainloop *);
        inline pa_context *(*pa_context_new)(pa_mainloop_api *, const char *);
        inline int (*pa_context_connect)(pa_context *, const char *, unsigned int, const void *);
        inline void (*pa_context_set_state_callback)(pa_context *, pa_context_notify_cb_t, void *);
        inline pa_operation *(*pa_context_load_module)(pa_context *, const char *, const char *, pa_context_index_cb_t,
                                                       void *);
        inline pa_operation *(*pa_context_get_module_info_list)(pa_context *, pa_module_info_cb_t, void *);
        inline pa_operation *(*pa_context_get_source_output_info_list)(pa_context *, pa_source_output_info_cb_t,
                                                                       void *);
        inline pa_operation *(*pa_context_get_sink_input_info_list)(pa_context *, pa_sink_input_info_cb_t, void *);
        inline pa_operation *(*pa_context_get_server_info)(pa_context *, pa_server_info_cb_t, void *);

        inline const char *(*pa_proplist_gets)(const pa_proplist *, const char *);

        inline pa_operation *(*pa_context_set_default_source)(pa_context *, const char *, pa_context_success_cb_t,
                                                              void *);
        inline pa_operation *(*pa_context_move_sink_input_by_name)(pa_context *, std::uint32_t, const char *,
                                                                   pa_context_success_cb_t, void *);
        inline pa_operation *(*pa_context_move_sink_input_by_index)(pa_context *, std::uint32_t, std::uint32_t,
                                                                    pa_context_success_cb_t, void *);
        inline pa_operation *(*pa_context_move_source_output_by_name)(pa_context *, std::uint32_t, const char *,
                                                                      pa_context_success_cb_t, void *);
        inline pa_operation *(*pa_context_move_source_output_by_index)(pa_context *, std::uint32_t, std::uint32_t,
                                                                       pa_context_success_cb_t, void *);
        inline pa_operation *(*pa_context_set_sink_input_mute)(pa_context *, uint32_t, int, pa_context_success_cb_t,
                                                               void *);
        inline pa_operation *(*pa_context_unload_module)(pa_context *, std::uint32_t, pa_context_success_cb_t, void *);
        inline pa_context_state (*pa_context_get_state)(const pa_context *);
        inline pa_operation_state (*pa_operation_get_state)(const pa_operation *);
    } // namespace PulseApi
} // namespace Soundux