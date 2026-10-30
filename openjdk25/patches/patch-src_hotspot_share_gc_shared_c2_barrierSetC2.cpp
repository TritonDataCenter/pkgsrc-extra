$NetBSD$

Upstream bug found by codex trying to figure out memory crash.

--- src/hotspot/share/gc/shared/c2/barrierSetC2.cpp.orig	2026-10-30 13:17:52.920531092 +0000
+++ src/hotspot/share/gc/shared/c2/barrierSetC2.cpp
@@ -1153,7 +1153,7 @@ void BarrierSetC2::compute_liveness_at_s
   Arena* const A = Thread::current()->resource_area();
   PhaseCFG* const cfg = C->cfg();
   PhaseRegAlloc* const regalloc = C->regalloc();
-  RegMask* const live = NEW_ARENA_ARRAY(A, RegMask, cfg->number_of_blocks() * sizeof(RegMask));
+  RegMask* const live = NEW_ARENA_ARRAY(A, RegMask, cfg->number_of_blocks());
   BarrierSetAssembler* const bs = BarrierSet::barrier_set()->barrier_set_assembler();
   BarrierSetC2State* bs_state = barrier_set_state();
   Block_List worklist;
