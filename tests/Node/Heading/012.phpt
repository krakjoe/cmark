--TEST--
CommonMark\Node\Heading incorrect isset
--FILE--
<?php
$heading = new CommonMark\Node\Heading();

var_dump(isset($heading->something));
?>
--EXPECT--
bool(false)
