--TEST--
CommonMark\Node\Custom isset onEnter
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

var_dump(isset($block->onEnter));

$block->onEnter = "OK";

var_dump(isset($block->onEnter));
?>
--EXPECT--
bool(false)
bool(true)
