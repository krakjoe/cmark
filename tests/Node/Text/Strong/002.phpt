--TEST--
CommonMark\Node\Text\Strong Bad Construct
--FILE--
<?php
try {
	new CommonMark\Node\Text\Strong([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
