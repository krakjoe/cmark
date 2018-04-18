--TEST--
CommonMark\CQL constraint Strong
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
strong __here__
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(Strong)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Text\Strong) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

