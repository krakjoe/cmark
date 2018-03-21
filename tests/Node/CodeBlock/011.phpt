--TEST--
CommonMark\Node\CodeBlock isset
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

$zero = 0;

var_dump(isset($block->$zero));

var_dump(isset($block->fence));

$block->fence = "OK";

var_dump(isset($block->fence));
?>
--EXPECT--
bool(false)
bool(false)
bool(true)
