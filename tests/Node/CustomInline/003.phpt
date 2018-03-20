--TEST--
CommonMark\Node\CustomInline onLeave
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

$node->onLeave = "OK";

echo $node->onLeave;
?>
--EXPECT--
OK
