--TEST--
CommonMark\Node\CodeBlock Fence
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;
$block->setFence("OK");

echo $block->getFence();
?>
--EXPECT--
OK
