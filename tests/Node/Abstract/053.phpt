--TEST--
CommonMark\Node isset lastChild
--FILE--
<?php
$doc = new CommonMark\Node\Document();
$doc->appendChild(new CommonMark\Node\Paragraph);

$f = function() use($doc) {
	return isset($doc->lastChild);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
