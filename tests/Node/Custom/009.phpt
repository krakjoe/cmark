--TEST--
CommonMark\Node\Custom isset onLeave
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

var_dump(isset($block->onLeave));

$block->onLeave = "OK";

var_dump(isset($block->onLeave));
?>
--EXPECT--
bool(false)
bool(true)
