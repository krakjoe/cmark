--TEST--
CommonMark\Node\CustomInline onEnter Error
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

try {
	$node->onEnter = [];
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
