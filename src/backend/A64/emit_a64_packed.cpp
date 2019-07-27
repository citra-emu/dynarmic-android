/* This file is part of the dynarmic project.
 * Copyright (c) 2016 MerryMage
 * This software may be used and distributed according to the terms of the GNU
 * General Public License version 2 or any later version.
 */

#include "backend/A64/block_of_code.h"
#include "backend/A64/emit_a64.h"
#include "frontend/ir/microinstruction.h"
#include "frontend/ir/opcodes.h"

namespace Dynarmic::BackendA64 {

void EmitA64::EmitPackedAddU8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg sum = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.ADD(B, sum, sum, b);

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.CMHI(B, ge, b, sum);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    ctx.reg_alloc.DefineValue(inst, sum);
}

void EmitA64::EmitPackedAddS8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.SQADD(B, ge, a, b);
        code.fp_emitter.CMGE_zero(B, ge, ge);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    code.fp_emitter.ADD(B, a, a, b);

    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedAddU16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg sum = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.ADD(H, sum, sum, b);

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.CMHI(H, ge, b, sum);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    ctx.reg_alloc.DefineValue(inst, sum);
}

void EmitA64::EmitPackedAddS16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.SQADD(H, ge, a, b);
        code.fp_emitter.CMGE_zero(H, ge, ge);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    code.fp_emitter.ADD(H, a, a, b);

    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSubU8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.CMHS(B, ge, a, b);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    code.fp_emitter.SUB(B, a, a, b);

    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSubS8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.SQSUB(B, ge, a, b);
        code.fp_emitter.CMGE_zero(B, ge, ge);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    code.fp_emitter.SUB(B, a, a, b);

    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSubU16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.CMHS(H, ge, a, b);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    code.fp_emitter.SUB(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSubS16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);
    const auto ge_inst = inst->GetAssociatedPseudoOperation(IR::Opcode::GetGEFromOp);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    if (ge_inst) {
        const ARM64Reg ge = EncodeRegToDouble(ctx.reg_alloc.ScratchFpr());

        code.fp_emitter.SQSUB(H, ge, a, b);
        code.fp_emitter.CMGE_zero(H, ge, ge);

        ctx.reg_alloc.DefineValue(ge_inst, ge);
        ctx.EraseInstruction(ge_inst);
    }

    code.fp_emitter.SUB(H, a, a, b);

    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingAddU8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UHADD(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);

}

void EmitA64::EmitPackedHalvingAddU16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UHADD(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingAddS8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SHADD(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingAddS16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SHADD(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingSubU8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UHSUB(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingSubS8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SHSUB(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingSubU16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UHSUB(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedHalvingSubS16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SHSUB(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}
void EmitA64::EmitPackedSaturatedAddU8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UQADD(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedAddS8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SQADD(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedSubU8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UQSUB(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedSubS8(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SQSUB(B, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedAddU16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UQADD(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedAddS16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SQADD(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedSubU16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.UQSUB(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}

void EmitA64::EmitPackedSaturatedSubS16(EmitContext& ctx, IR::Inst* inst) {
    auto args = ctx.reg_alloc.GetArgumentInfo(inst);

    const ARM64Reg a = EncodeRegToDouble(ctx.reg_alloc.UseScratchFpr(args[0]));
    const ARM64Reg b = EncodeRegToDouble(ctx.reg_alloc.UseFpr(args[1]));

    code.fp_emitter.SQSUB(H, a, a, b);
    ctx.reg_alloc.DefineValue(inst, a);
}
} // namespace Dynarmic::BackendA64
