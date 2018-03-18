--TEST--
CommonMark\Node\CustomBlock onEnter Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

if (!$node->getOnEnter()) {
	echo "OK";
}
?>
--EXPECT--
OK
