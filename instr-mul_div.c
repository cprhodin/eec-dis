
static inline void instr_mulu3_direct(cpu_context * cc)
{
    uint32_t op3   = read_16(cc, waop_direct(cc));
    uint32_t op2   = read_16(cc, fetch(cc));
    uint32_t lreg1 = fetch(cc);

    write_32(cc, lreg1, op2 * op3);
}

static inline void instr_mulu3_immediate(cpu_context * cc)
{
    uint32_t op3   = waop_immediate(cc);
    uint32_t op2   = read_16(cc, fetch(cc));
    uint32_t lreg1 = fetch(cc);

    write_32(cc, lreg1, op2 * op3);
}

static inline void instr_mulu3_indirect(cpu_context * cc)
{
    uint32_t op3   = read_16(cc, waop_indirect(cc));
    uint32_t op2   = read_16(cc, fetch(cc));
    uint32_t lreg1 = fetch(cc);

    write_32(cc, lreg1, op2 * op3);
}

static inline void instr_mulu3_indexed(cpu_context * cc)
{
    uint32_t op3   = read_16(cc, waop_indexed(cc));
    uint32_t op2   = read_16(cc, fetch(cc));
    uint32_t lreg1 = fetch(cc);

    write_32(cc, lreg1, op2 * op3);
}

static inline void instr_mulub3_direct(cpu_context * cc)
{
    uint32_t op3   = read_8(cc, baop_direct(cc));
    uint32_t op2   = read_8(cc, fetch(cc));
    uint32_t wreg1 = fetch(cc);

    write_16(cc, wreg1, op2 * op3);
}

static inline void instr_mulub3_immediate(cpu_context * cc)
{
    uint32_t op3   = baop_immediate(cc);
    uint32_t op2   = read_8(cc, fetch(cc));
    uint32_t wreg1 = fetch(cc);

    write_16(cc, wreg1, op2 * op3);
}

static inline void instr_mulub3_indirect(cpu_context * cc)
{
    uint32_t op3   = read_8(cc, baop_indirect(cc));
    uint32_t op2   = read_8(cc, fetch(cc));
    uint32_t wreg1 = fetch(cc);

    write_16(cc, wreg1, op2 * op3);
}

static inline void instr_mulub3_indexed(cpu_context * cc)
{
    uint32_t op3   = read_8(cc, baop_indexed(cc));
    uint32_t op2   = read_8(cc, fetch(cc));
    uint32_t wreg1 = fetch(cc);

    write_16(cc, wreg1, op2 * op3);
}

static inline void instr_mulu_direct(cpu_context * cc)
{
    uint32_t op2  = read_16(cc, waop_direct(cc));
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_mulu_immediate(cpu_context * cc)
{
    uint32_t op2  = waop_immediate(cc);
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_mulu_indirect(cpu_context * cc)
{
    uint32_t op2  = read_16(cc, waop_indirect(cc));
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_mulu_indexed(cpu_context * cc)
{
    uint32_t op2  = read_16(cc, waop_indexed(cc));
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_mulub_direct(cpu_context * cc)
{
    uint32_t op2  = read_8(cc, baop_direct(cc));
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

static inline void instr_mulub_immediate(cpu_context * cc)
{
    uint32_t op2  = baop_immediate(cc);
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

static inline void instr_mulub_indirect(cpu_context * cc)
{
    uint32_t op2  = read_8(cc, baop_indirect(cc));
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

static inline void instr_mulub_indexed(cpu_context * cc)
{
    uint32_t op2  = read_8(cc, baop_indexed(cc));
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul3_direct(cpu_context * cc)
{
}

// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul3_immediate(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul3_indirect(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul3_indexed(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb3_direct(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb3_immediate(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb3_indirect(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb3_indexed(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul_direct(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul_immediate(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul_indirect(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mul_indexed(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb_direct(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb_immediate(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb_indirect(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_mulb_indexed(cpu_context * cc)
{
}


static inline void instr_divu_direct(cpu_context * cc)
{
    uint32_t op2  = read_16(cc, waop_direct(cc));
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_divu_immediate(cpu_context * cc)
{
    uint32_t op2  = waop_immediate(cc);
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_divu_indirect(cpu_context * cc)
{
    uint32_t op2  = read_16(cc, waop_indirect(cc));
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_divu_indexed(cpu_context * cc)
{
    uint32_t op2  = read_16(cc, waop_indexed(cc));
    uint32_t lreg = fetch(cc);
    uint32_t op1  = read_16(cc, lreg);

    write_32(cc, lreg, op1 * op2);
}

static inline void instr_divub_direct(cpu_context * cc)
{
    uint32_t op2  = read_8(cc, baop_direct(cc));
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

static inline void instr_divub_immediate(cpu_context * cc)
{
    uint32_t op2  = baop_immediate(cc);
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

static inline void instr_divub_indirect(cpu_context * cc)
{
    uint32_t op2  = read_8(cc, baop_indirect(cc));
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

static inline void instr_divub_indexed(cpu_context * cc)
{
    uint32_t op2  = read_8(cc, baop_indexed(cc));
    uint32_t wreg = fetch(cc);
    uint32_t op1  = read_8(cc, wreg);

    write_16(cc, wreg, op1 * op2);
}

// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_div_direct(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_div_immediate(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_div_indirect(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_div_indexed(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_divb_direct(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_divb_immediate(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_divb_indirect(cpu_context * cc)
{
}


// Shift long register left
//  opcode:
//  flags: Z  N  C  V  VT ST I
//         ?  ?  ?  ?  ?  -  -
//
static inline void instr_divb_indexed(cpu_context * cc)
{
}

