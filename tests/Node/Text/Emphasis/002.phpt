--TEST--
CommonMark\Node\Text\Emphasis Bad Construct
--FILE--
<?php
try {
	new CommonMark\Node\Text\Emphasis([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
