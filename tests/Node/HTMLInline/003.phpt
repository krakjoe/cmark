--TEST--
CommonMark\Node\HTMLInline construct
--FILE--
<?php
$block = new CommonMark\Node\HTMLInline("OK");

echo $block->literal;
?>
--EXPECT--
OK
