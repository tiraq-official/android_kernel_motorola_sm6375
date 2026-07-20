/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM binder
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH trace/hooks
#if !defined(_TRACE_HOOK_BINDER_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_HOOK_BINDER_H
#include <linux/tracepoint.h>
#include <trace/hooks/vendor_hooks.h>
/*
 * Following tracepoints are not exported in tracefs and provide a
 * mechanism for vendor modules to hook and extend functionality
 */
#if defined(CONFIG_TRACEPOINTS) && defined(CONFIG_ANDROID_VENDOR_HOOKS)
struct binder_transaction;
struct binder_proc;
struct binder_thread;
struct binder_work;
struct list_head;
struct task_struct;
DECLARE_HOOK(android_vh_binder_transaction_init,
	TP_PROTO(struct binder_transaction *t),
	TP_ARGS(t));
DECLARE_HOOK(android_vh_binder_set_priority,
	TP_PROTO(struct binder_transaction *t, struct task_struct *task),
	TP_ARGS(t, task));
DECLARE_HOOK(android_vh_binder_restore_priority,
	TP_PROTO(struct binder_transaction *t, struct task_struct *task),
	TP_ARGS(t, task));
DECLARE_HOOK(android_vh_binder_special_task,
	TP_PROTO(struct binder_transaction *t, struct binder_proc *proc,
		struct binder_thread *thread, struct binder_work *w,
		struct list_head *head, bool sync, bool *special_task),
	TP_ARGS(t, proc, thread, w, head, sync, special_task));
DECLARE_HOOK(android_vh_binder_wait_for_work,
	TP_PROTO(bool do_proc_work, struct binder_thread *tsk, struct binder_proc *proc),
	TP_ARGS(do_proc_work, tsk, proc));
DECLARE_HOOK(android_vh_binder_proc_transaction_finish,
	TP_PROTO(struct binder_proc *proc, struct binder_transaction *t,
		struct task_struct *binder_th_task, bool pending_async, bool sync),
	TP_ARGS(proc, t, binder_th_task, pending_async, sync));
DECLARE_HOOK(android_vh_binder_proc_transaction_entry,
	TP_PROTO(struct binder_proc *proc, struct binder_transaction *t,
	struct binder_thread **thread, int node_debug_id, bool pending_async,
	bool sync, bool *skip),
	TP_ARGS(proc, t, thread, node_debug_id, pending_async, sync, skip));
DECLARE_HOOK(android_vh_binder_select_worklist_ilocked,
	TP_PROTO(struct list_head **list, struct binder_thread *thread, struct binder_proc *proc,
	int wait_for_proc_work),
	TP_ARGS(list, thread, proc, wait_for_proc_work));
DECLARE_HOOK(android_vh_binder_has_work_ilocked,
	TP_PROTO(struct binder_thread *thread, bool do_proc_work, int *ret),
	TP_ARGS(thread, do_proc_work, ret));
DECLARE_HOOK(android_vh_binder_read_done,
	TP_PROTO(struct binder_proc *proc, struct binder_thread *thread),
	TP_ARGS(proc, thread));
DECLARE_HOOK(android_vh_binder_looper_state_registered,
	TP_PROTO(struct binder_thread *thread, struct binder_proc *proc),
	TP_ARGS(thread, proc));
DECLARE_HOOK(android_vh_binder_thread_release,
	TP_PROTO(struct binder_proc *proc, struct binder_thread *thread),
	TP_ARGS(proc, thread));
DECLARE_HOOK(android_vh_binder_free_proc,
	TP_PROTO(struct binder_proc *proc),
	TP_ARGS(proc));
DECLARE_HOOK(android_vh_binder_preset,
	TP_PROTO(struct hlist_head *hhead, struct mutex *lock),
	TP_ARGS(hhead, lock));
#else
#define trace_android_vh_binder_transaction_init(t)
#define trace_android_vh_binder_set_priority(t, task)
#define trace_android_vh_binder_restore_priority(t, task)
#define trace_android_vh_binder_special_task(t, proc, thread, w, head, sync, special_task)
#define trace_android_vh_binder_wait_for_work(do_proc_work, tsk, proc)
#define trace_android_vh_binder_proc_transaction_finish(proc, t, binder_th_task, pending_async, sync)
#define trace_android_vh_binder_proc_transaction_entry(proc, t, thread, node_debug_id, pending_async, sync, skip)
#define trace_android_vh_binder_select_worklist_ilocked(list, thread, proc, wait_for_proc_work)
#define trace_android_vh_binder_has_work_ilocked(thread, do_proc_work, ret)
#define trace_android_vh_binder_read_done(proc, thread)
#define trace_android_vh_binder_looper_state_registered(thread, proc)
#define trace_android_vh_binder_thread_release(proc, thread)
#define trace_android_vh_binder_free_proc(proc)
#define trace_android_vh_binder_preset(hhead, lock)
#endif
#endif /* _TRACE_HOOK_BINDER_H */
/* This part must be outside protection */
#include <trace/define_trace.h>