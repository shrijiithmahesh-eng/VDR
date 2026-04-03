; VAC OS ACPI Shutdown (Simplified)
[bits 32]
vac_power_down:
    cli                     ; Disable Interrupts (Stop the "Blinks")
    mov ax, 0x2000          ; The "SLP_EN" (Sleep Enable) bit
    mov dx, [PM1a_CNT]      ; The Power Management Register
    out dx, ax              ; TRIGGER: THE VOID
    hlt                     ; If ACPI fails, HLT is the fallback
