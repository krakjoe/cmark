--TEST--
CommonMark\Node\CodeBlock Fence
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;
$block->fence = "OK";

echo $block->fence;
?>
--EXPECT--
OK
