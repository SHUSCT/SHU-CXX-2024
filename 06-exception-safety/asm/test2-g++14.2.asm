test2():
        push    r13
        push    r12
        push    rbp
        push    rbx
        sub     rsp, 8
        mov     rbp, QWORD PTR last[rip]
        mov     r13, QWORD PTR first[rip]
        mov     r12, QWORD PTR foo[rip]
        cmp     rbp, r13
        je      .L1
        mov     rbx, r13
.L3:
        mov     rsi, r12
        mov     rdi, rbx
        call    Foo::Foo(Foo const&) [complete object constructor]
        add     rbx, 1
        cmp     rbp, rbx
        jne     .L3
.L1:
        add     rsp, 8
        pop     rbx
        pop     rbp
        pop     r12
        pop     r13
        ret
        mov     rbp, rax
        jmp     .L4
test2() [clone .cold]:
.L5:
        mov     rdi, r13
        add     r13, 1
        call    Foo::~Foo() [complete object destructor]
.L4:
        cmp     r13, rbx
        jne     .L5
        mov     rdi, rbp
        call    _Unwind_Resume