--TEST--
CommonMark\Node\CustomInline onEnter Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

if (!$node->onEnter) {
	echo "OK";
}
?>
--EXPECT--
OK
