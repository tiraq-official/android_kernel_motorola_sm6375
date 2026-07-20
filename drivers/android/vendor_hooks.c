// SPDX-License-Identifier: GPL-2.0-only
/* vendor_hook.c
 *
 * Android Vendor Hook Support
 *
 * Copyright 2020 Google LLC
 */

#define CREATE_TRACE_POINTS
#include <trace/hooks/vendor_hooks.h>
#include <trace/hooks/sched.h>
#include <trace/hooks/dtask.h>
#include <trace/hooks/net.h>
#include <trace/hooks/binder.h>
#include <trace/hooks/rwsem.h>
#include <trace/hooks/futex.h>
#include <trace/hooks/fpsimd.h>
#include <trace/hooks/topology.h>
#include <trace/hooks/debug.h>
#include <trace/hooks/mm.h>
#include <trace/hooks/minidump.h>
#include <trace/hooks/wqlockup.h>
#include <trace/hooks/sysrqcrash.h>
#include <trace/hooks/cgroup.h>
#include <trace/hooks/sys.h>
#include <trace/hooks/vmscan.h>
#include <trace/hooks/fs.h>
#include <trace/hooks/gpu.h>
#include <trace/hooks/input.h>

/*
 * Export tracepoints that act as a bare tracehook (ie: have no trace event
 * associated with them) to allow external modules to probe them.
 */
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_select_task_rq_fair);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_select_task_rq_rt);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_select_fallback_rq);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_scheduler_tick);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_update_cpu_capacity);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_uclamp_eff_value);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_dynamic_svp_preempt);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_enqueue_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_dequeue_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_can_migrate_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_find_lowest_rq);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_rtmutex_prepare_setprio);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_prepare_prio_fork);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_finish_prio_fork);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_set_user_nice);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_setscheduler);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_sched_setaffinity_early);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mutex_wait_start);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mutex_wait_finish);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_read_wait_start);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_read_wait_finish);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_write_wait_start);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_write_wait_finish);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_sched_show_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_ptype_head);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_kfree_skb);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_sk_alloc);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_sk_free);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_nf_conn_alloc);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_nf_conn_free);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_arch_set_freq_scale);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_transaction_init);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_set_priority);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_restore_priority);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_special_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_wait_for_work);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_proc_transaction_finish);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_proc_transaction_entry);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_select_worklist_ilocked);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_has_work_ilocked);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_read_done);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_looper_state_registered);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_thread_release);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_free_proc);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_binder_preset);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_init);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_wake);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rwsem_write_finished);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_alter_rwsem_list_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_alter_futex_plist_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_is_fpsimd_save);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_ipi_stop);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_printk_store);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_show_regs);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_wq_lockup_pool);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_sysrq_crash);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_rvh_find_busiest_group);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_map_util_freq);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_em_pd_energy);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_rmqueue);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_cgroup_set_task);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_syscall_prctl_finished);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_tune_scan_type);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_tune_swappiness);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_tune_inactive_ratio);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mem_cgroup_id_remove);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mem_cgroup_css_offline);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mem_cgroup_css_online);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mem_cgroup_free);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_mem_cgroup_alloc);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_iolimit_rw);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_gpu_context_create);
EXPORT_TRACEPOINT_SYMBOL_GPL(android_vh_input_sync);