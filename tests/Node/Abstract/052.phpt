--TEST--
CommonMark\Node isset firstChild
--FILE--
<?php
$doc = new CommonMark\Node\Document();
$doc->appendChild(new CommonMark\Node\Paragraph);

$f = function() use($doc) {
	return isset($doc->firstChild);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
