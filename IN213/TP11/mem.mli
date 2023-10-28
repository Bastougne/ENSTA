val mem : VmBytecode.mem
val new_block :
  VmBytecode.vm_state -> int -> (VmBytecode.address * VmBytecode.vm_state)
val gc : VmBytecode.vm_state -> VmBytecode.vm_state
