--TEST--
CommonMark\CQL printer
--FILE--
<?php
$call = new \CommonMark\CQL(<<<EOD
/children(~CustomBlock|CustomInline)[
	/children(~ThematicBreak|SoftBreak|LineBreak)
]
EOD
);

$call->print();

echo PHP_EOL;

$call = new \CommonMark\CQL(<<<EOD
/firstChild(~CustomInline)[
	/children
]
EOD
);

$call->print();
?>
--EXPECTF--
---------------------------------------
Function Size:  %d
Function Space: %d bytes
Stack Size:     %d
Stack Space:    %d bytes
Total Space:    %d bytes
---------------------------------------
|OL	|INSTR	|IV	|RV/#T	|
---------------------------------------
 #0	 FCN	 0	 1	|loop
 #1	 CON	 1	 #9	|(~CustomBlock|CustomInline)
 #2	 FCN	 1	 2	|loop
 #3	 CON	 2	 #5	|(~ThematicBreak|SoftBreak|LineBreak)
 #4	 ENT	 2	 -	|-
 #5	 NEN	 2	 3	|
 #6	 SET	 2	 3	|-
 #7	 CON	 3	 #5	|(~ThematicBreak|SoftBreak|LineBreak)
 #8	 JMP	 3	 #4	|-
 #9	 NEN	 1	 4	|
 #10	 SET	 1	 4	|-
 #11	 CON	 4	 #9	|(~CustomBlock|CustomInline)
 #12	 JMP	 4	 #2	|-
 #13	 RET	 -	 -	|-
---------------------------------------

---------------------------------------
Function Size:  %d
Function Space: %d bytes
Stack Size:     %d
Stack Space:    %d bytes
Total Space:    %d bytes
---------------------------------------
|OL	|INSTR	|IV	|RV/#T	|
---------------------------------------
 #0	 FCN	 0	 1	|loop
 #1	 CON	 1	 #8	|(~CustomInline)
 #2	 FCN	 1	 2	|loop
 #3	 ENT	 2	 -	|-
 #4	 NEN	 2	 3	|
 #5	 SET	 2	 3	|-
 #6	 JMP	 3	 #3	|-
 #7	 BRK	 -	 #12	|-
 #8	 NEN	 1	 4	|
 #9	 SET	 1	 4	|-
 #10	 CON	 4	 #8	|(~CustomInline)
 #11	 JMP	 4	 #2	|-
 #12	 RET	 -	 -	|-
---------------------------------------

