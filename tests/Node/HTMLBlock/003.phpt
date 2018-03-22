--TEST--
CommonMark\Node\HTMLBlock construct
--FILE--
<?php
$block = new CommonMark\Node\HTMLBLock("OK");

echo $block->literal;
?>
--EXPECT--
OK
