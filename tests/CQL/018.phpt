--TEST--
CommonMark\CQL constraint Code
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
`code` here
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(Code)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Code) {
		echo "OK\n";
	}	
});
?>
--EXPECT--
OK

